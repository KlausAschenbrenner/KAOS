//
//  ListNode.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "List.h"
#include "ListNode.h"

// Creates a new ListNode
ListNode *NewListNode(void *Payload)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->Previous = (ListNode *)0x0;
    node->Next = (ListNode *)0x0;
    node->Payload = Payload;

    return node;
}