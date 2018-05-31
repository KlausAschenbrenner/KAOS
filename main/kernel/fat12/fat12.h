//
//  fat12.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_Fat12_h
#define KAOS_Fat12_h

#define KERNEL_IMAGE "KERNEL  BIN"

const int NumberOfFATs = 2;
const int SectorsPerFAT = 9;
const int SectorsPerCluster = 1;
const int ReservedSectors = 1;
const int RootEntries = 224;
const int BytesPerSector = 512;

const int ROOT_DIRECTORY_BUFFER = 0x30000;
const int FAT_BUFFER = 0x32000;
const int KERNEL_BUFFER = 0x100000;
const int EOF = 0x0FF0;

// Represents a Root Directory Entry
struct _RootDirectoryEntry
{
    unsigned char Filename[8];
    unsigned char Extension[3];
    unsigned char Attributes[1];
    unsigned char Reserved[2];
    unsigned char CreationTime[2];
    unsigned char CreationDate[2];
    unsigned char LastAccessDate[2];
    unsigned char Ignore[2];
    unsigned char LastWriteTime[2];
    unsigned char LastWriteDate[2];
    unsigned short FirstCluster;
    unsigned int FileSize;
} __attribute__ ((packed));
typedef struct _RootDirectoryEntry RootDirectoryEntry; 

// Loads some sectors from the Floppy Disk into memory
void ReadSectors(int StartSector, int Sectors, unsigned char *Buffer);

// Finds a given Root Directory Entry by its Filename
RootDirectoryEntry* FindRootDirectoryEntry(char *Filename);

unsigned short FATRead(unsigned short Cluster);

#endif
