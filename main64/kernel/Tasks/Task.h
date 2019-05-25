//
//  Task.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef TASK_H
#define TASK_H

#include "../ui/List.h"

// The various Task states
#define TASK_STATUS_CREATED       0x0
#define TASK_STATUS_RUNNABLE      0x1
#define TASK_STATUS_RUNNING       0x2
#define TASK_STATUS_WAITING       0x3

// Represents a Task
typedef struct _Task
{
    // General Purpose Registers
    unsigned long rax;
    unsigned long rbx;
    unsigned long rcx;
    unsigned long rdx;
    unsigned long rbp;
    unsigned long rsi;
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long r11;
    unsigned long r12;
    unsigned long r13;
    unsigned long r14;
    unsigned long r15;
    unsigned long cr3;

    unsigned long rdi;
    unsigned long rip;
    unsigned long cs;
    unsigned long rflags;
    unsigned long rsp;
    unsigned long ss;

    unsigned long ds;

    // The ID of the running Task
    int PID;

    // The used Kernel Mode Stack
    unsigned long KernelModeStack;

    // The number of context switches of the running Task
    unsigned long ContextSwitches;

    // The status of the Task:
    // 0: CREATED
    // 1: RUNNABLE
    // 2: RUNNING
    // 3: WAITING
    int Status;
} Task;

// Represents a list of Tasks (like the RUNNABLE queue)
typedef struct _TaskList
{
    struct TaskList *Previous;
    struct TaskList *Next;
    Task *Task;
} TaskList;

// Creates a new Kernel Task
Task* CreateKernelTask(void *TaskCode, int PID, long *KernelModeStack);

// Creates a new User Task
Task* CreateUserTask(void *TaskCode, int PID, long *UserModeStack, long *KernelModeStack);

// Adds a new Task at the tail of the RUNNABLE queue
void AddTaskToTaskQueue(Task *Task);

// Moves the current Task from the head of the RUNNABLE queue to the tail of the RUNNABLE queue.
Task* MoveToNextTask();

// Terminates the process with the given PID
int TerminateTask(int PID);

// Kills the process with the given PID
int KillTask(int PID);

// Dumps out the RUNNABLE queue
void DumpRunnableQueue();

// Returns a String List with the current running Tasks
List *GetTaskList();

// Dumps out the Task State structure of the current executed Task
void DumpTaskState();

// Returns a reference to the current Task State structure by returning the value from the register R15
extern long GetTaskState();

extern void AcquireLock(unsigned long Spinlock);

extern void ReleaseLock(unsigned long Spinlock);

#endif