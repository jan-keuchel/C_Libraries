#ifndef BBST_H
#define BBST_H

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    // Pointer to the data being stored in the specific node.
    void *data;
    // Pointer to children.
    struct node_t *left;
    struct node_t *right;
    // Height of the node.
    size_t height;
    // Function pointer for comparison of nodes
    int (*compare_to)(void *elem1, void *elem2);
} node_t;

typedef struct {
    size_t stride;
    node_t *root;
} BBST;

BBST *BBST_create(size_t capacity, int (*compare_to)(void *elem1, void *elem2));

#endif
