//
//  List.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "List.h"
#include "ListNode.h"
#include "../Heap/Heap.h"

// Creates a new List
List *NewList()
{
    // Creates a new List structure
    List *list = malloc(sizeof(List));
    list->Count = 0;
    list->RootNode = (ListNode *)0x0;

    return list;
}

// Adds a new Node to the given List
void AddNodeToList(List *List, void *Payload)
{
    ListNode *newNode = NewListNode(Payload);

    if (!List->RootNode)
    {
        // Add the first, initial Node to the List
        List->RootNode = newNode;
    }
    else
    {
        ListNode *currentNode = List->RootNode;
        
        // Move to the end of the List
        while (currentNode->Next)
            currentNode = currentNode->Next;

        // Add the new Node to the end of the List
        currentNode->Next = newNode;
        newNode->Previous = currentNode;
    }
    
    List->Count++;
}

// Removes a Node from the given List
void *RemoveNodeFromList(List *List, int Index)
{
    int currentIndex;
    void *payload;

    if (List->Count == 0 || Index >= List->Count)
        return (void *)0x0;

    ListNode *currentNode = List->RootNode;

    for (currentIndex = 0; (currentIndex < Index) && currentNode; currentIndex++)
        currentNode = (ListNode *)currentNode->Next;

    if (!currentNode)
        return (void *)0x0;

    payload = currentNode->Payload;

    if (currentNode->Previous)
    {
        ListNode *previous = (ListNode *)currentNode->Previous;
        previous->Next = currentNode->Next;
    }
    
    if (currentNode->Next)
    {
        ListNode *next = (ListNode *)currentNode->Next;
        next->Previous = currentNode->Previous;
    }

    if (Index == 0)
        List->RootNode = (ListNode *)currentNode->Next;

    // free(currentNode);

    List->Count--;

    return payload;
}

// Returns a Node from the given List
void *GetNodeFromList(List *List, int Index)
{
    if (List->Count == 0 || Index >= List->Count)
        return (void *)0x0;

    ListNode *currentNode = List->RootNode;
    int currentIndex;

    // Iterate through the List until we have found the requested Node
    for (currentIndex = 0; (currentIndex < Index) && currentNode; currentIndex++)
        currentNode = (ListNode *)currentNode->Next;

    // Return the requested Node if found - otherwise a NULL pointer
    return currentNode ? currentNode->Payload : (void *)0x0;
}