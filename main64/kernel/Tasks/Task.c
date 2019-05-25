//
//  Task.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "Task.h"
#include "../Heap/Heap.h"
#include "../structs/KPCR.h"
#include "../gdt/tss.h"

// Stores all Tasks to be executed
TaskList *TaskQueue = 0x0;

// Creates a new Kernel Task
Task* CreateKernelTask(void *TaskCode, int PID, long *KernelModeStack)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->rax = 0;
    newTask->rbx = 0;
    newTask->rcx = 0;
    newTask->rdx = 0;
    newTask->rbp = KernelModeStack;
    newTask->rsi = 0;
    newTask->r8 = 0;
    newTask->r9 = 0;
    newTask->r10 = 0;
    newTask->r11 = 0;
    newTask->r12 = 0;
    newTask->r13 = 0;
    // newTask->r14 = 0;           // Register R14 is currently not used, because it stores *globally* a reference to the KPCR Data Structure!
    newTask->r15 = newTask;     // We store the state of the Task in register R15
    newTask->cr3 = 0x90000;     // Page Table Address
    newTask->rdi = 0;
    newTask->rip = TaskCode;
    newTask->rflags = 0x2202;
    newTask->PID = PID;
    newTask->Status = TASK_STATUS_CREATED;

    // Set the Selectors for Ring 0
    newTask->cs = 0x8;
    newTask->ss = 0x10;
    newTask->ds = 0x10;

    // Prepare the stack of the new Task so that it looks like a traditional Stack Frame from an interrupt.
    // When we restore the state of this Task the first time, that Stack Frame is used during the IRETQ opcode.
    long *stack = KernelModeStack - 5;
    newTask->rsp = stack;
    stack[0] = TaskCode;            // RIP
    stack[1] = 0x8;                 // Code Segment/Selector for Ring 0
    stack[2] = 0x2202;              // RFLAGS
    stack[3] = KernelModeStack;     // Stack Pointer
    stack[4] = 0x10;                // Stack Segment/Selector for Ring 0

    // Add the newly created Task to the end of the Task queue
    AddTaskToTaskQueue(newTask);

    return newTask;
}

// Creates a new User Task
Task* CreateUserTask(void *TaskCode, int PID, long *UserModeStack, long *KernelModeStack)
{
    Task *newTask = malloc(sizeof(Task));
    newTask->rax = 0;
    newTask->rbx = 0;
    newTask->rcx = 0;
    newTask->rdx = 0;
    newTask->rbp = UserModeStack;
    newTask->rsi = 0;
    newTask->r8 = 0;
    newTask->r9 = 0;
    newTask->r10 = 0;
    newTask->r11 = 0;
    newTask->r12 = 0;
    newTask->r13 = 0;
    newTask->r14 = 0;
    newTask->r15 = newTask; // We store the state of the Task in register R15
    newTask->cr3 = 0x90000; // Page Table Address
    newTask->rdi = 0;
    newTask->rip = TaskCode;
    newTask->rflags = 0x2202;
    newTask->PID = PID;
    newTask->Status = TASK_STATUS_CREATED;
    newTask->KernelModeStack = KernelModeStack;

    // Set the Selectors for Ring 3
    newTask->cs = 0x1b;
    newTask->ss = 0x23;
    newTask->ds = 0x23;

    // Prepare the stack of the new Task so that it looks like a traditional Stack Frame from an interrupt.
    // When we restore the state of this Task the first time, that Stack Frame is used during the IRETQ opcode.
    long *stack = UserModeStack - 5;
    newTask->rsp = stack;
    stack[0] = TaskCode;            // RIP
    stack[1] = 0x1b;                // Code Segment/Selector for Ring 3 - with the requested RPL of 3
    stack[2] = 0x2202;              // RFLAGS
    stack[3] = UserModeStack;       // Stack Pointer
    stack[4] = 0x23;                // Stack Segment/Selector for Ring 3 - with the requested RPL of 3

    // Add the newly created Task to the end of the Task queue
    AddTaskToTaskQueue(newTask);

    return newTask;
}

// Adds a new Task at the tail of the Task queue
void AddTaskToTaskQueue(Task *Task)
{
    // Create a new Task entry for the Task queue
    TaskList *newEntry = malloc(sizeof(TaskList));
    newEntry->Next = 0x0;
    newEntry->Task = Task;

    // Check if the Task queue is already initialized
    if (TaskQueue == 0x0)
    {
        // If the Task queue is not yet initialized, the new Task is currently
        // the only one in the Task queue
        TaskQueue = newEntry;
        newEntry->Previous = 0x0;
    }
    else
    {
        TaskList *temp = TaskQueue;

        // Iterate through the Task queue, until we find the tail of it
        while (temp->Next != 0)
            temp = temp->Next;

        // Put the new Task at the tail of the Task queue
        temp->Next = newEntry;
        newEntry->Previous = temp;
    }
}

// Moves the current Task from the head of the Task queue to the tail of the Task queue.
Task* MoveToNextTask()
{
    TaskList *start = TaskQueue;
    TaskList *temp = TaskQueue;

    // Remove the Task at the head of the Task queue and set its status to RUNNING
    TaskQueue = TaskQueue->Next;
    TaskQueue->Task->Status = TASK_STATUS_RUNNING;
    TaskQueue->Previous = 0x0;

    // Iterate through the Task queue, until we find the tail of it
    while (temp->Next != 0x0)
        temp = temp->Next;

    // Add the old head of the Task queue to the tail of the Task queue and set its status to Task
    temp->Next = start;
    start->Next = 0x0;
    start->Previous = temp;
    start->Task->Status = TASK_STATUS_RUNNABLE;

    // Record the Context Switch
    TaskQueue->Task->ContextSwitches++;

    // Store the Kernel Mode Stack of the next Task to be scheduled in the TSS
    KPCR *kpcr = (KPCR *)GetKPCR();
    Task *task = TaskQueue->Task;
    TSSEntry *tss = kpcr->TSS;
    tss->rsp0 = task->KernelModeStack;

    // Return the next Task to be executed
    return TaskQueue->Task;
}

// Kills the process with the given PID
int KillTask(int PID)
{
    return TerminateTask(PID);
}

// Terminates the process with the given PID
int TerminateTask(int PID)
{
    TaskList *temp = TaskQueue;
    TaskList *currentTask = 0x0;
    TaskList *previousTask = 0x0;
    TaskList *nextTask = 0x0;

    // Iterate through the Task queue, until we find the given PID
    while (temp->Next != 0)
    {
        if (temp->Task->PID == PID)
            currentTask = temp;
        
        temp = temp->Next;
    }

    // Check the last entry in the Task queue (that one is not covered by the previous while loop)
    if (temp->Task->PID == PID)
            currentTask = temp;

    if (currentTask != 0x0)
    {
        // If we have to remove the head of the Task queue, we set the new head to the 2nd entry in the Task queue.
        // This also implies that the next call to "MoveToNextTask" moves that Task to the end of the Task queue.
        // Therefore we need a whole cycle through the Task queue, so that this Task is scheduled again...
        if (currentTask->Previous == 0x0)
        {
            TaskQueue = TaskQueue->Next;
        }
        else
        {
            // Remove the Task from the Task queue
            previousTask = currentTask->Previous;
            nextTask = currentTask->Next;
            previousTask->Next = nextTask;
            nextTask->Previous = previousTask;
        }

        return 1;
    }
    else
        // The given PID was not found
        return 0;

    // Schedule the next Task
    // Irq0_ContextSwitching(); // Causes an 0xD fault when executed through the KillTask code path...
}

// Returns a String List with the current running Tasks
List *GetTaskList()
{
    TaskList *temp = TaskQueue;
    List *tasks = NewList();
    char *str = malloc(10);

    itoa(temp->Task->PID, 10, str);
    AddNodeToList(tasks, str);

    // Iterate through the Task queue, until we find the tail of it
    while (temp->Next != 0)
    {
        // Move to the next Task in the Task queue
        temp = temp->Next;

        str = malloc(10);
        itoa(temp->Task->PID, 10, str);
        AddNodeToList(tasks, str);
    }

    return tasks;
}

// Dumps out the Task queue
void DumpTaskQueue()
{
    TaskList *temp = TaskQueue;

    // Print the current Task from the Task queue
    printf("PID: ");
    printf_int(temp->Task->PID, 10);
    printf(", next PID: ");
    TaskList *next = temp->Next;
    printf_int(next->Task->PID, 10);
    printf(", previous PID: N/A");
    printf(", Status: ");
    printf_int(temp->Task->Status, 10);
    printf("\n");

    // Iterate through the Task queue, until we find the tail of it
    while (temp->Next != 0)
    {
        // Move to the next Task in the Task queue
        temp = temp->Next;

        // Print the current Task from the Task queue
        printf("PID: ");
        printf_int(temp->Task->PID, 10);
        printf(", next PID: ");
        TaskList *next = temp->Next;

        if (temp->Next != 0x0)
            printf_int(next->Task->PID, 10);
        else
            printf("N/A");

        printf(", previous PID: ");
        TaskList *previous = temp->Previous;
        printf_int(previous->Task->PID, 10);

        printf(", Status: ");
        printf_int(temp->Task->Status, 10);
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