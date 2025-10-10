#include "dynlist.h"
#include <stdio.h>
#include <string.h>

/**
* `DL_create` allocates data for the DynList struct and it's data
* with the speicified `capacity` and size of elements `stride` on 
* the heap. In case of allocation failure it returns `NULL`.
*/
DynList* DL_create(size_t capacity, size_t stride, int (*compare_to)(void *elem1, void *elem2)) {
    // Allocate memory on the heap for the DynList struct.
    DynList *dl  = (DynList *) calloc(1, sizeof(DynList)); 
    if (dl == NULL) {
        fprintf(stderr, "Error allocating memory for DynList struct: %s\n", strerror(errno));
        return NULL;
    }

    // Initialize components
    dl->capacity   = capacity;
    dl->stride     = stride;
    dl->size       = 0;
    dl->compare_to = compare_to;

    // Allocate memory for data.
    dl->data     = (char *) calloc(capacity, stride);
    if (dl->data == NULL) {
        fprintf(stderr, "Error allocating memory for DynList Data: %s\n", strerror(errno));
        free(dl);
        return NULL;
    }

    // Return pointer to DynList struct.
    return dl;
}

/**
* `DL_free` frees all memory of the DynLists data and the struct itself.
*/
void DL_free(DynList *dl) {
    // Check for empty DynList.
    if (dl == NULL) {
        return;
    }

    // Free data of DynList.
    if (dl->data != NULL) {
        free(dl->data);
    }

    // Free DynList struct.
    free(dl);
}


/**
* `DL_append` adds another `element` to the DynList `dl`.
* If the current capacity of `dl` is not sufficient, it is doubled.
* Returns 0 on success and -1 on failure.
*/
int DL_append(DynList *dl, void *element) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given: Can't append.");
        return -1;
    }

    // Reallocate data if list is full.
    if (dl->size == dl->capacity) {
        // Allocate new data.
        char *new_data = (char *) realloc(dl->data, dl->stride * dl->capacity * 2);
        if (new_data == NULL) {
            fprintf(stderr, "DL_append failed to reallocate memory to increase capacity of DynList: %s\n", strerror(errno));
            return -1;
        }

        // Update dl pointer and capacity.
        dl->data = new_data;
        dl->capacity *= 2;
    }

    // Copy new element into DynList.
    void *new_item = memcpy(dl->data + dl->stride * dl->size, element, dl->stride);
    if (new_item == NULL) {
        fprintf(stderr, "memcpy failed to copy new element into DynList.\n");
        return -1;
    }
    dl->size++;

    return 0;
}

/**
* `DL_get` returns a void pointer to the element indexed by the 
* provided `index`. Checks for out of bounds errors based on
* the size of the DynList. Thus, it is only possible to index into
* the parts of the DynList that have been populated with elements. 
* Not the entire capacity.
*/
void* DL_get(DynList *dl, size_t index) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given to DL_get.");
        return NULL;
    }

    if (index >= dl->size) {
        fprintf(stderr, "Index out of bounds for DL_get: index=%zu, size=%zu\n", index, dl->size);
        return NULL;
    }

    return (void *) (dl->data + index * dl->stride);
}

/**
 * `DL_pop` allocates space on the heap for 1 element
 * copies the element ad the given `index` into said memory
 * and returns a pointer to it.
 * `free()` needs to be called manually!
 */
void* DL_pop(DynList *dl, size_t index) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given to DL_pop.");
        return NULL;
    }

    if (index >= dl->size) {
        fprintf(stderr, "Index out of bounds for DL_pop: index=%zu, size=%zu\n", index, dl->size);
        return NULL;
    }

    // Allocate memory for return
    void *result = malloc(dl->stride);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation for result failed in DL_pop.\n");
        return NULL;
    }

    // copy over element
    if (memcpy(result, dl->data + index * dl->stride, dl->stride) == NULL) {
        fprintf(stderr, "Failed to copy return value to different address.\n");
        return NULL;
    }

    // Move elements in DynList one element to the left.
    void *dst = memmove(dl->data + (index) * dl->stride,
                        dl->data + (index+1) * dl->stride, 
                        dl->stride * (dl->size - index - 1));
    if (dst == NULL) {
        fprintf(stderr, "DL_pop failed to move elements to the left: %s\n", strerror(errno));
        return NULL;
    }

    dl->size--;

    return result;
}

/**
* `DL_clear` sets the `size` of `dl` to 0. The memory is not set to 0.
* The capacity remains unchanged.
*/
void DL_clear(DynList *dl) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given to DL_clear.");
        return;
    }

    dl->size = 0;
}

/**
* `DL_size` returns the size of the DynList: the number of elements
* currently in the list. 
* Returns 0 on success, -1 otherwise.
*/
int DL_size(DynList *dl) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given to DL_size.");
        return -1;
    }
    return dl->size;
}

/**
* `DL_is_empty` returns 0 if `dl` is empty, 1 if it 
* is not and -1 if the provided DynList was not initialized.
*/
int DL_is_empty(DynList *dl) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given to DL_is_empty.");
        return -1;
    }
    return dl->size == 0 ? 0 : 1;
}

/**
* `DL_insert` adds `element` at the specified `index` to the DynList.
* Returns 0 on success, -1 on failure.
*/
int DL_insert(DynList *dl, void *element, size_t index) {
    if (dl == NULL) {
        fprintf(stderr, "Non-initialized DynList was given to DL_insert.");
        return -1;
    }

    // Check if DynList capacity needs to be doubled
    if (dl->size == dl->capacity) {
        // Allocate new data.
        char *new_data = (char *) realloc(dl->data, dl->stride * dl->capacity * 2);
        if (new_data == NULL) {
            fprintf(stderr, "DL_insert failed to reallocate memory to increase capacity of DynList: %s\n", strerror(errno));
            return -1;
        }

        // Update dl pointer and capacity.
        dl->data = new_data;
        dl->capacity *= 2;
    }

    // copy dl[index] - dl[size-1] one slot to the right
    void *dst = memmove(dl->data + (index+1) * dl->stride,
                        dl->data + index * dl->stride, 
                        dl->stride * (dl->size - index));
    if (dst == NULL) {
        fprintf(stderr, "DL_insert failed to move elements: %s\n", strerror(errno));
        return -1;
    }

    // insert new item
    dst = memcpy(dl->data + index * dl->stride, element, dl->stride);
    if (dst == NULL) {
        fprintf(stderr, "DL_insert failed to copy new element into list: %s\n", strerror(errno));
        return -1;
    }

    dl->size++;

    return 0;
}

/**
* `DL_set` sets the element of `dl` at the specified `index` to
* the given `element`. `index` need be smaller than the size of `dl`.
* returns 0 on success, -1 otherwise.
*/
int DL_set(DynList *dl, void *element, int index) {
    if (dl == NULL) {
        fprintf(stderr, "DL_set error: provided DynList is NULL.\n");
        return -1;
    }

    // check for out of bounds index.
    if (index >= dl->size) {
        fprintf(stderr, "DL_set error: index out of bounds.\n");
        return -1;
    }

    // Copy bytes of elem into specified index.
    void *dst = memcpy(dl->data + dl->stride * index, element, dl->stride);
    if (dst == NULL) {
        fprintf(stderr, "DL_set error: Failed to copy element into DynList.\n");
        return -1;
    }

    return 0;
}

/**
* `DL_extend` appends `dl2` to `dl1`. Both DynLists need to have 
* the same stride and compare_to function. The new capacity of `dl1`
* is the sum of the capacities of `dl1` and `dl2`.
*/
int DL_extend(DynList *dl1, DynList *dl2) {
    if (dl1 == NULL || dl2 == NULL) {
        fprintf(stderr, "DL_extend error: one of the provided DynList is NULL.\n");
        return -1;
    }

    if (dl1->stride != dl2->stride) {
        fprintf(stderr, "DL_extend error: functions with different strides given.\n");
        return -1;
    }

    // find new capacity
    size_t new_capacity = dl1->capacity;
    while (new_capacity < dl1->size + dl2->size) {
        new_capacity *= 2;
    }

    // Adjust capacity of dl1
    if (new_capacity != dl1->capacity) {
        // Allocate new data.
        char *new_data = (char *) realloc(dl1->data, dl1->stride * new_capacity);
        if (new_data == NULL) {
            fprintf(stderr, "DL_extend failed to reallocate memory to increase capacity of DynList: %s\n", strerror(errno));
            return -1;
        }

        // Update dl pointer and capacity.
        dl1->data = new_data;
        dl1->capacity = new_capacity;
    }

    // copy over data
    void *dst = memcpy(dl1->data + dl1->stride * dl1->size, 
                       dl2->data, 
                       dl2->size * dl2->stride);
    if (dst == NULL) {
        fprintf(stderr, "DL_extend error: Failed to copy data to dl1.\n");
        return -1;
    }

    // update size
    dl1->size += dl2->size;

    return 0;
}


/**
* `DL_reverse` reverses `dl` in place. returns 0 on success, -1 otherwise.
*/
int DL_reverse(DynList *dl) {
    if (dl == NULL) {
        fprintf(stderr, "DL_reverse error: provided DynList is NULL.\n");
        return -1;
    }

    char temp[dl->stride];
    for (int i = 0; i < dl->size / 2; i++) {
        void *dst = memcpy(temp, dl->data + dl->stride * i, dl->stride);
        if (dst == NULL) {
            fprintf(stderr, "DL_reverse error: failed to copy data into temporary variable.\n");
            return -1;
        }
        DL_set(dl, dl->data + dl->stride * (dl->size - i - 1), i);
        DL_set(dl, temp, dl->size - i - 1);
    }

    return 0;
}

/**
* `DL_count` returns the number of occurrences of `elem` in `dl`.
* returns -1 on failure.
*/
int DL_count(DynList *dl, void *elem) {
    if (dl == NULL) {
        fprintf(stderr, "DL_count error: provided DynList is NULL.\n");
        return -1;
    }

    int n = 0;
    for (int i = 0; i < dl->size; i++) {
        if (dl->compare_to(dl->data + dl->stride * i, elem) == 0) {
            n++;
        }
    }

    return n;
}

/**
* `DL_contains` returns 1 if `elem` occurrs in `dl`,
* 0 if it does not and -1 on failure.
*/
int DL_contains(DynList *dl, void *elem) {
    if (dl == NULL) {
        fprintf(stderr, "DL_contains error: provided DynList is NULL.\n");
        return -1;
    }

    for (int i = 0; i < dl->size; i++) {
        if (dl->compare_to(dl->data + dl->stride * i, elem) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
* `DL_index` returns the index of the first occurrence 
* of `elem` in `dl`. Returns -1 on failure and -2 if 
* `elem` does not occur in `dl`.
*/
int DL_index(DynList *dl, void *elem) {
    if (dl == NULL) {
        fprintf(stderr, "DL_index error: provided DynList is NULL.\n");
        return -1;
    }

    for (int i = 0; i < dl->size; i++) {
        if (dl->compare_to(dl->data + dl->stride * i, elem) == 0) {
            return i;
        }
    }

    return -2;
}

/**
* `DL_copy` returns a new DynList that contains the elements
* from index `start` to `end`, of which `start` is inclusive
* while `end` is exclusive.
*/
DynList *DL_copy(DynList *dl, int start, int end) {
    if (dl == NULL) {
        fprintf(stderr, "DL_copy error: provided DynList is NULL.\n");
        return NULL;
    }

    // Check for index out of bounds.
    if (start < 0 || end > dl->size || start >= end) {
        fprintf(stderr, "DL_copy error: index out of bounds.\n");
        return NULL;
    }

    // Create new DynList.
    DynList *res = DL_create(2*(end - start), dl->stride, dl->compare_to);
    if (res == NULL) {
        fprintf(stderr, "DL_copy error: failed to create new DynList.\n");
        return NULL;
    }

    // Copy data into new DynList
    void *dst = memcpy(res->data, 
                       dl->data + dl->stride * start, 
                       dl->stride * (end - start));
    if (dst == NULL) {
        fprintf(stderr, "DL_copy error: Copying data into new DynList failed.\n");
        return NULL;
    }

    // Update size of resulting DynList
    res->size = end - start;

    return res;
}

void merge(DynList *dl, int left, int m, int right) {
    int pL = left;
    int pR = m + 1;
    DynList *buffer = DL_create(dl->capacity, dl->stride, dl->compare_to);
    buffer->size = buffer->capacity;

    for (int i = left; i <= right; i++) {
        if (pR > right ||
            (pL <= m && dl->compare_to(DL_get(dl, pL), DL_get(dl, pR)) <= 0)) {

            DL_set(buffer, DL_get(dl, pL), i - left);
            pL++;
        } else {
            DL_set(buffer, DL_get(dl, pR), i - left);
            pR++;
        }
    }

    for (int i = left; i <= right; i++) {
        DL_set(dl, DL_get(buffer, i - left), i);
    }

}

void merge_sort(DynList *dl, int left, int right) {
    if (left < right) {
        int m = (left + right) / 2;
        merge_sort(dl, left, m);
        merge_sort(dl, m+1, right);
        merge(dl, left, m, right);
    }
}

/**
* `DL_sort` sorts the given DynList `dl` based on the 
* specified compare function `compare_to`. This is done inplace.
* Returns 0 on success, -1 otherwise.
*/
int DL_sort(DynList *dl) {
    if (dl == NULL) {
        fprintf(stderr, "DL_sort error: provided DynList is NULL.\n");
        return -1;
    }

    if (dl->compare_to == NULL) {
        fprintf(stderr, "DL_sort error: DynList doesn't have a compare_to function specified.\n");
        return -1;
    }

    merge_sort(dl, 0, dl->size-1);

    return 0;
}

/**
* `DL_remove` removes the first ocurrence of `elem` from `dl`.
* returns 0 on success, -1 otherwise.
*/
int DL_remove(DynList *dl, void *elem) {
    if (dl == NULL) {
        fprintf(stderr, "DL_remove error: provided DynList is NULL.\n");
        return -1;
    }

    // find index of first occurrence.
    int index = -1;
    for (int i = 0; i < dl->size; i++) {
        if (dl->compare_to(DL_get(dl, i), elem) == 0) {
            index = i;
            break;
        }
    }

    // elem is not in dl
    if (index == -1) {
        return 0;
    }

    // elem is last item in dl
    if (index == dl->size - 1) {
        dl->size--;
        return 0;
    }

    // shift items to the left
    void *dst = memmove(dl->data + dl->stride * index, 
                        dl->data + dl->stride * (index + 1), 
                        dl->stride * (dl->size - index));
    if (dst == NULL) {
        fprintf(stderr, "DL_remove error: moving of data failed.\n");
        return -1;
    }

    // update size
    dl->size--;

    return 0;
}
