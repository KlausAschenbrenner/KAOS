//
//  main.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "syscalls/syscall.h"

void Sleep(int Iterations);

void main()
{
	char *string = "Karin Hochstoeger\0";
	int pid = RaiseSysCall(SYSCALL_GET_PID, "");
	int i;

	RaiseSysCall(SYSCALL_PRINTF, "\n");
	RaiseSysCall(SYSCALL_PRINTF_INT, (int *)&pid);
	RaiseSysCall(SYSCALL_PRINTF, "\n");
	
	for (i = 0; i < 10; i++)
	{
		// Print out a string
		RaiseSysCall(SYSCALL_PRINTF, string);
		RaiseSysCall(SYSCALL_PRINTF, "\n");
		
		// Introduce some delay in the calculation...
		Sleep(99999999);
	}

	// Terminate the current Task
	RaiseSysCall(SYSCALL_TERMINATE_TASK, 0);
}

void Sleep(int Iterations)
{
    int i;

	for (i = 0; i < Iterations; i++)
	{
        int a;
        int b;
        int c;
        a = 1;
        b = 1;
        c = a + b;
    }
}