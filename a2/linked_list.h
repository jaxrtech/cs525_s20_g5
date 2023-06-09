#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <stddef.h>
#include "freespace.h"

typedef struct BM_LinkedListElement {
    uint32_t index;
    void *data;
    struct BM_LinkedListElement *next;
    struct BM_LinkedListElement *prev;
} BM_LinkedListElement;

typedef struct BM_LinkedList {
    void *elementsDataBuffer;
    BM_LinkedListElement *elementsMetaBuffer;
    FS_Freespace *freespace;
    uint32_t count;
    size_t elementSize;
    BM_LinkedListElement *sentinel;
    BM_LinkedListElement *head;
    BM_LinkedListElement *tail;
} BM_LinkedList;

BM_LinkedList *LinkedList_create(uint32_t count, size_t elementSize);
void LinkedList_free(BM_LinkedList *list);
BM_LinkedListElement *LinkedList_fresh(BM_LinkedList *self);
bool LinkedList_isEmpty(BM_LinkedList *list);
void LinkedList_unlink(BM_LinkedList *list, BM_LinkedListElement *el);
bool LinkedList_remove(BM_LinkedList *self, BM_LinkedListElement *el);
void LinkedList_prepend(BM_LinkedList *list, BM_LinkedListElement *el);
void LinkedList_append(BM_LinkedList *list, BM_LinkedListElement *el);

void LinkedList_insertAfter(
        BM_LinkedList *list,
        BM_LinkedListElement *item,
        BM_LinkedListElement *reference);

void LinkedList_insertBefore(
        BM_LinkedList *list,
        BM_LinkedListElement *item,
        BM_LinkedListElement *reference);

bool LinkedList_replace(
        BM_LinkedList *list,
        BM_LinkedListElement *replacement,
        BM_LinkedListElement *existing);

#endif //__LINKED_LIST_H__
