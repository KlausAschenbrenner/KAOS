//
//  Task.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef TASK_H
#define TASK_H

// The various Task states
#define TASK_STATUS_CREATED       0x0
#define TASK_STATUS_RUNNABLE      0x1
#define TASK_STATUS_RUNNING       0x2
#define TASK_STATUS_WAITING       0x3

// Represents a Task
typedef struct _Task
{
    // General Purpose Registers
    long rax;
    long rbx;
    long rcx;
    long rdx;
    long rbp;
    long rsi;
    long r8;
    long r9;
    long r10;
    long r11;
    long r12;
    long r13;
    long r14;
    long r15;
    long cr3;

    long rdi;
    long rip;
    long cs;
    long rflags;
    long rsp;
    long ss;

    long ds;

    // The ID of the running Task
    int PID;

    // The used Kernel Mode Stack
    long KernelModeStack;

    // The number of context switches of the running Task
    long ContextSwitches;

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

// Dumps out the Task State structure of the current executed Task
void DumpTaskState();

// Returns a reference to the current Task State structure by returning the value from the register R15
extern long GetTaskState();

#endif