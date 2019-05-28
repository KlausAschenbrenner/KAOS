//
//  shell.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "Heap/Heap.h"

// The number of available commands
#define COMMAND_COUNT 10

void shell_cls(char *param);
void shell_dir(char *param);
void shell_ps(char *param);
void shell_tasks(char *param);
void shell_heap(char *param);
void shell_kpcr(char *param);
void shell_kill(char *param);
void shell_status(char *param);
void shell_help(char *param);
void shell_dummy(char *param);

// The available Shell commands
char *commands[] =
{
	"cls",
	"dir",
	"ps",
	"tasks",
	"heap",
	"kpcr",
	"kill",
	"status",
	"help",
	"dummy"
};

int (*command_functions[]) (char *param) =
{
	&shell_cls,
	&shell_dir,
	&shell_ps,
	&shell_tasks,
	&shell_heap,
	&shell_kpcr,
	&shell_kill,
	&shell_status,
	&shell_help,
	&shell_dummy
};

void Shell()
{
	// ClearScreen();
    int i;
	
    while (1 == 1)
	{
		// AcquireLock(&spinlock);

		char input[100] = "";
		int commandFound = 0;
		printf("A:\>");
		scanf(input, 98);

        for (i = 0; i < COMMAND_COUNT; i++)
        {
            // Execute the specified command
			if (StartsWith(input, commands[i]) == 1)
            {
                (*command_functions[i])(&input);
                commandFound = 1;
            }
        }

        if (commandFound == 0)
        {
            // Try to load the requested program into memory
			if (LoadProgram(input) != 0)
			{
				// The program was loaded successfully into memory.
				// Let's execute it as a User Task!
				CreateUserTask(0xFFFF8000FFFF0000, 9, 0xFFFF800001900000, 0xFFFF800000090000);
			}
			else
			{
				printf("'");
				printf(input);
				printf("' is not recognized as an internal or external command,\n");
				printf("operable program or batch file.\n\n");
			}
        }
    }
}

void shell_cls(char *param)
{
    ClearScreen();
}

void shell_dir(char *param)
{
    PrintRootDirectory();
}

void shell_ps(char *param)
{
	DumpTaskState();
}

void shell_tasks(char *param)
{
    DumpTaskQueue();
}

void shell_heap(char *param)
{
	DumpHeap();
}

void shell_kpcr(char *param)
{
	DumpKPCR();
}

void shell_kill(char *param)
{
	// Extract the PID to kill
	char temp[5] = "";
	substring(param, 5, strlen(param), temp);
	int pid = atoi(temp);

	// Kill the Task
	if (KillTask(pid) == 0)
		printf("The given PID was not found.\n");
}

void shell_status(char *param)
{
	// Print out the calculated value from the other running Task...
	long *value = (long *)0xFFFF800000700000;
	printf("Calculation result from the different running Task: ");
	printf_long(*value, 10);
	printf("\n");
}

void shell_help(char *param)
{
	int i;
    printf("The following commands are available: \n");

	for (i = 0; i < COMMAND_COUNT; i++)
	{
		printf("   ");
		printf(commands[i]);
		printf("\n");
	}
}

void shell_dummy(char *param)
{
	printf("Dummy called");
}