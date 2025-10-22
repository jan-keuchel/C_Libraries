#include "bbst.h"

short get_height(node_t *n) {
    if (n == NULL) {
        fprintf(stderr, "get_height was given NULL node.\n");
        return 0;
    }
    return n->height;
}

short get_balance(node_t *n) {
    if (n == NULL) {
        fprintf(stderr, "get_balance was given NULL node.\n");
        return 0;
    }
    return get_height(n->right) - get_height(n->left);
}


