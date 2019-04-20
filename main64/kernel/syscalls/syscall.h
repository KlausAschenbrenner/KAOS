//
//  syscall.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_syscall_h
#define KAOS_syscall_h

// Defines the various available SysCalls
#define SYSCALL_PRINTF 1
#define SYSCALL_TERMINATE_TASK 2

// Implements the SysCall Handler
void SysCallHandlerC(int SysCallNumber, void *Parameters);

#endif