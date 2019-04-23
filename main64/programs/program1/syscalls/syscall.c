//
//  syscall.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 23.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "syscall.h"

int RaiseSysCall(int SysCallNumber, void *Parameters)
{
    if (SysCallNumber == SYSCALL_TERMINATE_TASK)
    {
        RaiseSysCallAsm(SYSCALL_PRINTF, "Terminating current Task...\0");
        RaiseSysCallAsm(SysCallNumber, Parameters);

        // Just enter an infinite while loop so that the Kernel can terminate the Task in the mean time
        while (1 == 1);
    }
    else
        return RaiseSysCallAsm(SysCallNumber, Parameters);
}