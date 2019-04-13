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
    newTask->r15 = newTask;
    newTask->cr3 = 0x90000;
    newTask->PID = PID;

    /* long *stack = Stack - 5;
    newTask->rsp = stack;
    stack[0] = TaskCode;    // RIP
    stack[1] = 0x8;         // Code Segment/Selector
    stack[2] = 0x2202;      // RFLAGS
    stack[3] = Stack;       // Stack Pointer
    stack[4] = 0x10;        // Stack Segment/Selector */

    long *stack = Stack - 5;
    stack[0] = TaskCode;    // RIP
    stack[1] = 0x8;         // Code Segment/Selector
    stack[2] = 0x2202;      // RFLAGS
    stack[3] = Stack;       // Stack Pointer
    stack[4] = 0x10;        // Stack Segment/Selector

    newTask->rip = TaskCode;
    newTask->cs = 0x8;
    newTask->rflags = 0x2202;
    newTask->rsp = Stack;
    newTask->ss = 0x10;

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

// Switches to the next Task.
// This function gets called by the Timer Interrupt.
void SwitchTask()
{
    cntr++;

    /* int oldRow, oldCol;
    GetCursorPosition(&oldRow, &oldCol);
    SetCursorPosition(25, 80);

    if (cntr % 2 == 0)
        print_char('A');
    else
        print_char('B');

    SetCursorPosition(oldRow, oldCol); */

    // Switch to the next Task (implemented in Assembler)
    TaskList *nextEntry = RunnableQueue->Next;
    TaskSwitch(RunnableQueue->Task, nextEntry->Task);
}

// Moves the current Task from the head of the RUNNABLE queue to the tail of the RUNNABLE queue.
void MoveToNextTask()
{
    TaskList *start = RunnableQueue;
    TaskList *temp = RunnableQueue;

    // Remove the Task at the head of the RUNNABLE queue
    RunnableQueue = RunnableQueue->Next;

    // Iterate through the RUNNABLE queue, until we find the tail of it
    while (temp->Next != 0)
        temp = temp->Next;

    // Add the old head of the RUNNABLE queue to the tail of the RUNNABLE queue
    temp->Next = start;
    start->Next = 0x0;

    DumpRunnableQueue();
}

// Dumps out the RUNNABLE queue
void DumpRunnableQueue()
{
    TaskList *temp = RunnableQueue;

    // Print the 1st Task in the RUNNABLE queue
    printf("Task #");
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