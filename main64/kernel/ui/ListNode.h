//
//  List.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_ListNode_h
#define KAOS_ListNode_h

// Defines a Node in a Double Linked List
typedef struct _ListNode
{
    void *Payload;
    struct _List *Previous;
    struct _List *Next;
} ListNode;

// Creates a new ListNode
ListNode *NewListNode(void *Payload);

#endif