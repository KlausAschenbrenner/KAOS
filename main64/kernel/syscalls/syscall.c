//
//  syscall.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "syscall.h"
#include "../Tasks/Task.h"
#include "../structs/KPCR.h"

// Implements the SysCall Handler
int SysCallHandlerC(int SysCallNumber, void *Parameters)
{
    // printf
    if (SysCallNumber == SYSCALL_PRINTF)
    {
        printf(Parameters);
        return 0;
    }
    // printf_int
    else if (SysCallNumber == SYSCALL_PRINTF_INT)
    {
        int value = *(int *)Parameters;
        printf_int(value, 10);
        return 0;
    }
    // TerminateTask
    else if (SysCallNumber == SYSCALL_TERMINATE_TASK)
    {
        Task *state = (Task *)GetTaskState();
        TerminateTask(state->PID);
        return 0;
    }
    // Get PID
    else if (SysCallNumber == SYSCALL_GET_PID)
    {
        Task *state = (Task *)GetTaskState();
        return state->PID;
    }
}