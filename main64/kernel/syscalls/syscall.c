//
//  syscall.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "syscall.h"
#include "../Tasks/Task.h"

// Implements the SysCall Handler
void SysCallHandlerC(int SysCallNumber, void *Parameters)
{
    // printf
    if (SysCallNumber == SYSCALL_PRINTF)
    {
        printf(Parameters);
    }
    // TerminateTask
    else if (SysCallNumber == SYSCALL_TERMINATE_TASK)
    {
        Task *state = (Task *)GetTaskState();
        TerminateTask(state->PID);
    }
}