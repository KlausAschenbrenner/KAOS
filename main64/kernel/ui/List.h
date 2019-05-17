//
//  List.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_List_h
#define KAOS_List_h

#include "ListNode.h"

// Defines a simple Doube Linked List
typedef struct _List
{
    int Count;
    ListNode *RootNode;
} List;

// Creates a new List
List *NewList();

// Adds a new Node to the given List
void AddNodeToList(List *List, void *Payload);

// Removes a Node from the given List
void *RemoveNodeFromList(List *List, int Index);

// Returns a Node from the given List
void *GetNodeFromList(List *List, int Index);

#endif