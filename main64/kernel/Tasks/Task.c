//
//  Task.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "Task.h"
#include "../Heap/Heap.h"

int cntr = 0;

// Stores all Tasks in the RUNNABLE state
TaskList *RunnableQueue = 0x0;

// Creates a new Kernel Task
Task* CreateKernelTask(void *TaskCode, int PID, void *Stack)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->rax = 0;
    newTask->rbx = 0;
    newTask->rcx = 0;
    newTask->rdx = 0;
    newTask->rbp = 0;
    newTask->rsi = 0;
    newTask->r8 = 0;
    newTask->r9 = 0;
    newTask->r10 = 0;
    newTask->r11 = 0;
    newTask->r12 = 0;
    newTask->r13 = 0;
    newTask->r14 = 0;
    newTask->r15 = newTask; // We store the state of the Task in register R15
    newTask->cr3 = 0x90000;

    newTask->rdi = 0;
    newTask->rip = TaskCode;
    newTask->cs = 0x8;
    newTask->rflags = 0x2202;
    // newTask->rsp = Stack;
    newTask->ss = 0x10;

    newTask->PID = PID;

    // long *stack = Stack - 5;
    // newTask->rsp = stack;

    // Prepare the stack of the new Task so that it looks like a traditional Stack Frame from an interrupt.
    // When we restore the state of this Task the first time, that Stack Frame is used during the IRETQ opcode.
    long *stack = Stack - 40; // ???? No idea why, but it is needed... ;-)
    newTask->rsp = stack;
    stack[0] = TaskCode;    // RIP
    stack[1] = 0x08;        // Code Segment/Selector
    stack[2] = 0x2202;      // RFLAGS
    stack[3] = stack;       // Stack Pointer
    stack[4] = 0x10;        // Stack Segment/Selector

    // Add the newly created Task to the end of the RUNNABLE queue
    AddTaskToRunnableQueue(newTask);

    return newTask;
}

// Adds a new Task at the tail of the RUNNABLE queue
void AddTaskToRunnableQueue(Task *Task)
{
    // Create a new Task entry for the RUNNABLE queue
    TaskList *newEntry = malloc(sizeof(TaskList));
    newEntry->Next = 0x0;
    newEntry->Task = Task;

    // Check if the RUNNABLE queue is already initialized
    if (RunnableQueue == 0x0)
    {
        // If the RUNNABLE queue is not yet initialized, the new Task is currently
        // the only one in the RUNNABLE queue
        RunnableQueue = newEntry;
    }
    else
    {
        TaskList *temp = RunnableQueue;

        // Iterate through the RUNNABLE queue, until we find the tail of it
        while (temp->Next != 0)
            temp = temp->Next;

        // Put the new Task at the tail of the RUNNABLE queue
        temp->Next = newEntry;
    }
}

// Moves the current Task from the head of the RUNNABLE queue to the tail of the RUNNABLE queue.
Task* MoveToNextTask()
{
    TaskList *start = RunnableQueue;
    TaskList *temp = RunnableQueue;

    // Remove the Task at the head of the RUNNABLE queue
    RunnableQueue = RunnableQueue->Next;

    // Iterate through the RUNNABLE queue, until we find the tail of it
    while (temp->Next != 0x0)
        temp = temp->Next;

    // Add the old head of the RUNNABLE queue to the tail of the RUNNABLE queue
    temp->Next = start;
    start->Next = 0x0;

    // Record the Context Switch
    RunnableQueue->Task->ContextSwitches++;

    // Return the next Task to be executed
    return RunnableQueue->Task;
}

// Dumps out the RUNNABLE queue
void DumpRunnableQueue()
{
    TaskList *temp = RunnableQueue;

    // Print the 1st Task in the RUNNABLE queue
    printf("PID: ");
    printf_int(temp->Task->PID, 10);
    printf("\n");

    // Iterate through the RUNNABLE queue, until we find the tail of it
    while (temp->Next != 0)
    {
        // Move to the next Task in the RUNNABLE queue
        temp = temp->Next;

        // Print the current Task from the RUNNABLE queue
        printf("Task #");
        printf_int(temp->Task->PID, 10);
        printf("\n");
    }
}

void DumpTaskState()
{
    // Get a reference to the current Task state
    Task *state = (Task *)GetTaskState();

    printf("PID: ");
    printf_int(state->PID, 10);
    printf("\n");
    printf("Number of Context Switches: ");
    printf_int(state->ContextSwitches, 10);
    printf("\n");
}