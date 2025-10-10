#ifndef DYNLIST_H
#define DYNLIST_H

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 10

typedef struct DynList {
    char    *data;
    size_t  capacity;
    size_t  size;
    size_t  stride;
    int     (*compare_to)(void *elem1, void *elem2);
} DynList;

DynList* DL_create(size_t capacity, size_t stride, int (*compare_to)(void *elem1, void *elem2));
void DL_free(DynList *dl);
int DL_append(DynList *dl, void *element);
void* DL_get(DynList *dl, size_t index);
void DL_clear(DynList *dl);
int DL_size(DynList *dl);
int DL_is_empty(DynList *dl);
int DL_insert(DynList *dl, void *element, size_t index);
int DL_set(DynList *dl, void *element, int index);
void* DL_pop(DynList *dl, size_t index);
int DL_extend(DynList *dl1, DynList *dl2);
int DL_reverse(DynList *dl);
int DL_count(DynList *dl, void *elem);
int DL_contains(DynList *dl, void *elem);
int DL_index(DynList *dl, void *elem);
int DL_sort(DynList *dl);
DynList *DL_copy(DynList *dl, int start, int end);


#endif // DYNLIST_H
