# DynList: A dynamic and generic list library for C

`DynList` is a dynamic and generic list implementation in C.
It's designed to mimic Pythons `list`.

## Features
- **Dynamic Resizing**: Automatically grows (doubles capacity) when needed.
- **Generic Elements**: Supports any data type via `void*` and a user-defined `stride` (aka size of a single element).
- **Custom Comparison**: For certain functions such as sorting of the `DynList` a comparison between elements is needed. Hence, a `compare_to` function pointer must be provided. If this is not needed `NULL` can always be provided.

### `DynList` struct
A `DynList` is structured as follows:
```C
typedef struct DynList {
    // A Pointer to the data being stored on the heap.
    char *data;
    // Number of elements that can be stored (memory allocated thus far).
    size_t capacity;
    // Number of elements stored in the list thus far.
    size_t size;
    // Number of bytes each element needs.
    size_t stride;
    // A function pointer in order to compare two elements for searching etc..
    int (*compare_to)(void *elem1, void *elem2);
} DynList;
```

### Functions
- **DL_create(capacity, stride, compare_to)**: Initialize the list and allocate memory.
- **DL_free(dl)**: Free all memory associated with the list and it's data.
- **DL_append(dl, element)**: Add another element to the end of the list.
- **DL_get(dl, index)**: Get a pointer to the value at the specified index.
- **DL_clear(dl)**: Set the size of the DynList to 0.
- **DL_size(dl)**: Get the size of the DynList.
- **DL_is_empty(dl)**: Check if the list is empty (aka the size is 0).
- **DL_insert(dl, element, index)**: Add a new element at the specified index.
- **DL_set(dl, element, index)**: Set the value at the specified index.
- **DL_pop(dl, index)**: Get a pointer to a newly allocated element which is removed from the DynList.
- **DL_extend(dl1, dl2)**: Append one DynList to another.
- **DL_reverse(dl)**: Reverse the list in-place.
- **DL_count(dl, elem)**: Count occurrences of the specified element (`compare_to` function must be given).
- **DL_contains(dl, elem)**: Check if an element exists in the DynList (`compare_to` function must be given).
- **DL_index(dl, elem)**: Get the index of the first occurrence of the element (`compare_to` function must be given).
- **DL_sort(dl)**: Sort the list in-place based (`compare_to` function must be given).
- **DL_copy(dl, start, end)**: Returns a new DynList with elements from `start` to `end`.
- **DL_remove(dl, elem)**: Remove an element from the DynList (`compare_to` function must be given).

## Installation
(TODO)

## Usage Example
(TODO)

```C
#include <stdio.h>
#include <stdlib.h>

#include <dynlist.h>

typedef struct {
    int id;
    int age;
    float height;
} person_t;

void print_person(person_t *p) {
    printf("Person Info:\n");
    printf("ID:      %d\n", p->id);
    printf("Age:     %d\n", p->age);
    printf("Height:  %.2f cm\n", p->height);  
}

/**
* `compare_people` returns...
* `x < 0` iff a < b <=> a.id < b.id
* `x = 0` iff a = b <=> a.id = b.id
* `x > 0` iff a > b <=> a.id > b.id
*/
int compare_people(void *a, void *b) {
    return (((person_t *)a)->id - ((person_t *)b)->id);
}

int main() {

    // ----- Using the `Person` struct -----
    // Create the new DynList with initial capacity of 2
    DynList *people = DL_create(2, sizeof(person_t), compare_people);

    // Some new people:
    person_t p1 = {
        .id = 0,
        .age = 22,
        .height = 1.80f
    };
    person_t p2 = {
        .id = 1,
        .age = 42,
        .height = 1.84f
    };
    person_t p3 = {
        .id = 2,
        .age = 12,
        .height = 1.40f
    };
    person_t p4 = {
        .id = 3,
        .age = 82,
        .height = 1.76f
    };

    // Add people to the list
    DL_append(people, &p3);
    DL_append(people, &p1);
    DL_append(people, &p4);
    DL_append(people, &p2);

    // Print the list
    for (int i = 0; i < DL_size(people); i++) {
        print_person(DL_get(people, i));
        printf("---------------------------\n");
    }

    // Sort the list based on the function pointer
    DL_sort(people);

    // Print again
    for (int i = 0; i < DL_size(people); i++) {
        print_person(DL_get(people, i));
        printf("---------------------------\n");
    }

    // Free DynList
    DL_free(people);

    return EXIT_SUCCESS;
}
```

**Output of the first print:**
```Bash
Person Info:
ID:      2
Age:     12
Height:  1.40 cm
---------------------------
Person Info:
ID:      0
Age:     22
Height:  1.80 cm
---------------------------
Person Info:
ID:      3
Age:     82
Height:  1.76 cm
---------------------------
Person Info:
ID:      1
Age:     42
Height:  1.84 cm
---------------------------
```

**Output of the second print:**
```Bash
Person Info:
ID:      0
Age:     22
Height:  1.80 cm
---------------------------
Person Info:
ID:      1
Age:     42
Height:  1.84 cm
---------------------------
Person Info:
ID:      2
Age:     12
Height:  1.40 cm
---------------------------
Person Info:
ID:      3
Age:     82
Height:  1.76 cm
---------------------------
```
