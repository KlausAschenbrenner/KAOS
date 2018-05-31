//
//  fat12.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "fat12.h"

// Loads the FAT12 Root Directory
void LoadRootDirectory()
{
    char str[32] = "";
    int head = 0;
    int track = 0;
    int sector = 0;

    // Calculate the Root Directory Size: 14 sectors
    short rootDirectorySectors = 32 * RootEntries / BytesPerSector;

    // Calculate the LBA address of the Root Directory
    short lbaAddressRootDirectory = NumberOfFATs  * SectorsPerFAT + ReservedSectors;

    ReadRootDirectory(lbaAddressRootDirectory, rootDirectorySectors);
}

void ReadRootDirectory(int StartSector, int Sectors)
{
    int i = 0;
    char str[32] = "";

    for (i = 0; i < Sectors; i++)
    {
        flpydsk_read_sector(i);
        flpydsk_reset();

        itoa(i + 1, 10, str);
        printf(str);
        printf("\n");
    }

    printf("Finished");
}