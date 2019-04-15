//
//  Task.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef TASK_H
#define TASK_H

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

    // The ID of the running Task
    int PID;

    // The number of context switches of the running Task
    long ContextSwitches;
} Task;

// Represents a list of Tasks (like the RUNNABLE queue)
typedef struct _TaskList
{
    struct TaskList *Next;
    Task *Task;
} TaskList;

// Creates a new Kernel Task
Task* CreateKernelTask(void *TaskCode, int PID, void *Stack);

// Adds a new Task at the tail of the RUNNABLE queue
void AddTaskToRunnableQueue(Task *Task);

// Moves the current Task from the head of the RUNNABLE queue to the tail of the RUNNABLE queue.
Task* MoveToNextTask();

// Dumps out the RUNNABLE queue
void DumpRunnableQueue();

// Dumps out the Task State structure of the current executed Task
void DumpTaskState();

extern long GetTaskState();

#endif