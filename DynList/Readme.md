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

## License
(TODO)
