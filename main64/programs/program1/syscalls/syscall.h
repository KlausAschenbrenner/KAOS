//
//  syscall.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

// Raises a SysCall through INT 0x80
extern void RaiseSysCall(int SysCallNumber, void *Parameter);

// Defines the various available SysCalls
#define SYSCALL_PRINTF 1
#define SYSCALL_TERMINATE_TASK 2