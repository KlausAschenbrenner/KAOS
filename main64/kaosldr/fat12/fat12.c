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
    // Calculate the Root Directory Size: 14 sectors: => 32 * 224 / 512
    short rootDirectorySectors = 32 * RootEntries / BytesPerSector;

    // Calculate the LBA address of the Root Directory: 19: => 2 * 9 + 1
    short lbaAddressRootDirectory = NumberOfFATs * SectorsPerFAT + ReservedSectors;

    // Load the whole Root Directory (14 sectors) into memory
    ReadSectors(lbaAddressRootDirectory, rootDirectorySectors, (unsigned char *)ROOT_DIRECTORY_BUFFER);

    // Load the whole FAT (18 sectors) into memory
    ReadSectors(1, NumberOfFATs * SectorsPerFAT, (unsigned char *)FAT_BUFFER);

    // Find the Root Directory Entry for KERNEL.BIN
    RootDirectoryEntry *entry = FindRootDirectoryEntry(KERNEL_IMAGE);

    if (entry != 0)
    {
        unsigned char *kernel_buffer = (unsigned char *)KERNEL_BUFFER;
        
        // Read the first cluster of the Kernel into memory
        ReadSectors(entry->FirstCluster + 33 - 2, 1, (unsigned char *)kernel_buffer);
        unsigned short nextCluster = FATRead(entry->FirstCluster);

        // Read the whole file into memory until we reach the EOF mark
        while (nextCluster < EOF)
        {
            kernel_buffer = kernel_buffer + BytesPerSector;
            ReadSectors(nextCluster + 33 - 2, 1, (unsigned char *)kernel_buffer);

            // Read the next Cluster from the FAT table
            nextCluster = FATRead(nextCluster);
        }

        // printf("KERNEL.BIN was successfully loaded into memory.\n");

        /* int i;
        char str[32] = "";
        unsigned char *kernel = 0x105400;

        for (i = 0; i < 512; i++)
        {
            itoa(kernel[i], 16, str);
            printf("0x");
            printf(str);
        } */
    }
    else
    {
        printf("KERNEL.BIN was not found.\n");
    }
}

unsigned short FATRead(unsigned short Cluster)
{
    // Calculate the offset into the FAT table
    unsigned int fatOffset = (Cluster / 2) + Cluster;
    unsigned short *offset = FAT_BUFFER + fatOffset;

    // Read the entry from the FAT
    unsigned short val = *offset;

    if (Cluster & 0x0001)
    {
        // Odd Cluster
        return val >> 4; // Highest 12 Bits
    }
    else
    {
        // Even Cluster
        return val & 0x0FFF; // Lowest 12 Bits
    }
}

// Finds a given Root Directory Entry by its Filename
RootDirectoryEntry* FindRootDirectoryEntry(char *Filename)
{
    RootDirectoryEntry *entry = (RootDirectoryEntry *)ROOT_DIRECTORY_BUFFER;
    int i;

    for (i = 0; i < 16; i++)
    {
        if (entry->Filename[0] != 0x00)
        {
            // Check if we got the Root Directory Entry in which we are interested in
            if (strcmp(entry->Filename, Filename, 11) == 0)
                return entry;
        }

        // Move to the next Root Directory Entry
        entry = entry + 1;
    }

    // The requested Root Directory Entry was not found
    return 0;
}

// Loads some sectors from the Floppy Disk into memory
void ReadSectors(int StartSector, int Sectors, unsigned char *Buffer)
{
    int i = 0;

    for (i = StartSector; i < StartSector + Sectors; i++)
    {
        // Load the requested sector from the Floppy Disk
        unsigned char *dmaBuffer = (unsigned char *)flpydsk_read_sector(i);
        flpydsk_reset();

        // Copy the loaded sector into the destination memory area
        memcpy(Buffer, dmaBuffer, BytesPerSector);
        Buffer = Buffer + BytesPerSector;
    }
}