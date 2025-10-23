#include "bbst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short get_height(node_t *n) {
    if (n == NULL) {
        fprintf(stderr, "get_height was given NULL node.\n");
        return 1;
    }
    return n->height;
}

short get_balance(node_t *n) {
    if (n == NULL) {
        fprintf(stderr, "get_balance was given NULL node.\n");
        return 1;
    }
    return get_height(n->right) - get_height(n->left);
}

node_t *node_create(void *data,
                    size_t stride,
                    size_t height,
                    int (*compare_to)(void *elem1, void *elem2)) {

    if (data == NULL) {
        fprintf(stderr, "create_node was given NULL value.\n");
        return NULL;
    }

    // Allocate memory for the node struct on heap.
    node_t *n = (node_t*)calloc(1, sizeof(node_t));
    if (n == NULL) {
        fprintf(stderr, "create_node failed to allocate memory for the node.\n");
        return NULL;
    }

    // Allocate memory for the data of the node on the heap.
    n->data = calloc(1, stride);
    if (n->data == NULL) {
        fprintf(stderr, "create_node failed to allocate memory for the dta.\n");
        free(n);
        return NULL;
    }

    // Copy data into node.
    void *dst = memcpy(n->data, data, stride);
    if (dst == NULL) {
        fprintf(stderr, "create_node failed to copy data into node.\n");
        free(n->data);
        free(n);
        return NULL;
    }

    // Set other members.
    n->stride     = stride;
    n->left       = NULL;
    n->right      = NULL;
    n->height     = height;
    n->compare_to = compare_to;

    return n;
}

void node_free_rec(node_t *current) {
    if (current->left != NULL) {
        node_free_rec(current->left);
    }
    if (current->right != NULL) {
        node_free_rec(current->right);
    }
    free(current->data);
    free(current);
}

node_t *node_insert(node_t *current,
                    void *data,
                    size_t stride,
                    size_t height,
                    int (*compare_to)(void *elem1, void *elem2)) {

    if (compare_to(data, current->data) <= 0) {
        printf("node_insert: new element smaller than current.\n");
        if (current->left == NULL) {
            printf("node_insert: child is NULL. Creating node.\n");
            current->left = node_create(data, stride, height+1, compare_to);
        } else {
            printf("node_insert: child exists. Descending...\n");
            current->left = node_insert(current->left, data, stride, height+1, compare_to);
        }
    } else {
        printf("node_insert: new element larger than current.\n");
        if (current->right == NULL) {
            printf("node_insert: child is NULL. Creating node.\n");
            current->right = node_create(data, stride, height+1, compare_to);
        } else {
            printf("node_insert: child exists. Descending...\n");
            current->right = node_insert(current->right, data, stride, height+1, compare_to);
        }
    }

    return current;
}

node_t *ror(node_t *n) {
    if (n == NULL) {
        fprintf(stderr, "ror was given empty node.\n");
        return NULL;
    }
    if (n->left == NULL) {
        fprintf(stderr, "ror was given node with no left child.\n");
        return NULL;
    }

    node_t *l_temp = n->left;
    n->left = n->left->right;
    l_temp->right = n;

    return l_temp;
}

node_t *rol(node_t *n) {
    if (n == NULL) {
        fprintf(stderr, "rol was given empty node.\n");
        return NULL;
    }
    if (n->right == NULL) {
        fprintf(stderr, "rol was given node with no right child.\n");
        return NULL;
    }

    node_t *r_temp = n->right;
    n->right = n->right->left;
    r_temp->left = n;

    return r_temp;
}


BBST *BBST_create(size_t stride, int (*compare_to)(void *elem1, void *elem2)) {
    BBST *bbst = (BBST *)calloc(1, sizeof(BBST));
    if (bbst == NULL) {
        fprintf(stderr, "BBST_create failed to allocate memory for BBST.\n");
        return NULL;
    }

    bbst->root       = NULL;
    bbst->stride     = stride;
    bbst->compare_to = compare_to;

    return bbst;
}

void BBST_free(BBST *bbst) {
    if (bbst->root != NULL) {
        node_free_rec(bbst->root);
    }
    free(bbst);
}

int BBST_insert(BBST *bbst, void *data) {
    if (bbst->root == NULL) {
        bbst->root = node_create(data, bbst->stride, 0, bbst->compare_to);
        return 0;
    }

    bbst->root = node_insert(bbst->root, data, bbst->stride, 0, bbst->compare_to);

    return 0;
}


