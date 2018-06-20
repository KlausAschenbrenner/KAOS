//
//  fat12.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_Fat12_h
#define KAOS_Fat12_h

const int NumberOfFATs = 2;
const int SectorsPerFAT = 9;
const int SectorsPerCluster = 1;
const int ReservedSectors = 1;
const int RootDirectoryEntries = 224;
const int BytesPerSector = 512;
unsigned char *PROGRAM_BUFFER = 0xFFFF8000FFFF0000;
unsigned char *ROOT_DIRECTORY_BUFFER;
unsigned char *FAT_BUFFER;
const int EOF = 0x0FF0;
int RootDirectoryLoaded = 0;

// Represents a Root Directory Entry - 32 bytes long
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

// Prints the Root Directory
void PrintRootDirectory();

// Load the given program into memory
int LoadProgram(unsigned char *Filename);

// Loads the Root Directory into memory
static void LoadRootDirectory();

// Finds a given Root Directory Entry by its Filename
static RootDirectoryEntry* FindRootDirectoryEntry(unsigned char *Filename);

// Loads some sectors from the Floppy Disk into memory
static void ReadSectors(int StartSector, int Sectors, unsigned char *Buffer);

// Load all Clusters for the given Root Directory Entry into memory
static void LoadProgramIntoMemory(RootDirectoryEntry *Entry);

// Reads the next FAT Entry from the FAT Tables
static unsigned short FATRead(unsigned short Cluster);

#endif