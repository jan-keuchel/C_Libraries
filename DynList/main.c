#include <stdio.h>
#include <stdlib.h>

#include "dynlist.h"

struct Person {
    int id;
    int age;
    float height;
};

void printPerson(struct Person *p) {
    // printf("Person Info:\n");
    printf("ID:      %d\n", p->id);
    // printf("Age:     %d\n", p->age);
    // printf("Height:  %.2f cm\n", p->height);  
}

int compare_ints(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}

int compare_people(void *a, void *b) {
    return (((struct Person *)a)->id - ((struct Person *)b)->id);
}

int main() {

    printf("Testing...");
    DynList *dl = DL_create(2, sizeof(int), &compare_ints);
    if (dl == NULL) {
        printf("DL_create failed miserably...");
        return EXIT_FAILURE;
    }

    printf("is empty=%b\n", DL_is_empty(dl) == 0);

    for (int i = 0; i < 10; i++) {
        DL_append(dl, &i);
    }

    printf("is empty=%b\n", DL_is_empty(dl) == 0);

    for (int i = 0; i < 10; i++) {
        printf("dl[%d] = %d\n", i, *(int *) DL_get(dl, i));
    }

    printf("Size=%d\n", DL_size(dl));

    DL_free(dl);

    printf("------------------------------------\n");

    DynList *pdl = DL_create(4, sizeof(struct Person), compare_people);

    struct Person p1 = {
        .age = 21,
        .height = 1.76,
        .id = 69
    };
    struct Person p2 = {
        .age = 18,
        .height = 1.68,
        .id = 0
    };
    struct Person p3 = {
        .age = 20,
        .height = 1.72,
        .id = 1
    };
    struct Person p4 = {
        .age = 100,
        .height = 1.22,
        .id = 999
    };
    struct Person p5 = {
        .age = 30,
        .height = 1.80,
        .id = 2
    };
    struct Person p6 = {
        .age = 25,
        .height = 1.65,
        .id = 88
    };
    struct Person p7 = {
        .age = 45,
        .height = 1.90,
        .id = 55
    };
    struct Person p8 = {
        .age = 60,
        .height = 1.55,
        .id = 55
    };
    struct Person p9 = {
        .age = 12,
        .height = 1.40,
        .id = 112
    };
    struct Person p10 = {
        .age = 75,
        .height = 1.60,
        .id = 18277
    };

    DL_append(pdl, &p1);
    DL_append(pdl, &p2);
    DL_append(pdl, &p3);

    for (int i = 0; i < DL_size(pdl); i++) {
        printPerson((struct Person*) DL_get(pdl, i));
    }

    printf("\nInserting at index 1:\n\n");
    if (DL_insert(pdl, &p4, 1) != 0) {
        printf("Error while inserting...\n");
    }

    for (int i = 0; i < DL_size(pdl); i++) {
        printPerson((struct Person*) DL_get(pdl, i));
    }


    printf("\nPopping off:\n\n");
    while (DL_size(dl) > 0) {
        struct Person *p = (struct Person*) DL_pop(pdl, DL_size(pdl) - 1);
        printPerson(p);
        free(p);
    }

    DL_free(pdl);


    printf("------------------------------------\n");
    printf("------------------------------------\n");

    DynList *idl = DL_create(2, sizeof(int), compare_ints);
    DynList *idl2 = DL_create(10, sizeof(int), compare_ints);

    int num_nums = 5;
    for (int i = 0; i < num_nums; i++) {
        DL_append(idl, &i);
    }
    for (int i = 1000; i < 1000+num_nums; i++) {
        DL_append(idl2, &i);
    }

    for (int i = 0; i < num_nums; i++) {
        printf("dl[%d]  = %d\n", i, *(int *) DL_get(idl, i));
        printf("dl2[%d] = %d\n", i, *(int *) DL_get(idl2, i));
    }

    printf("Size dl=%d\n", DL_size(idl));
    printf("Size dl2=%d\n", DL_size(idl2));

    printf("--- Extending ---\n");
    DL_extend(idl, idl2);

    for (int i = 0; i < DL_size(idl); i++) {
        printf("dl[%d]  = %d\n", i, *(int *) DL_get(idl, i));
    }
    for (int i = 0; i < DL_size(idl2); i++) {
        printf("dl2[%d]  = %d\n", i, *(int *) DL_get(idl2, i));
    }

    printf("--- Reversing ---\n");
    DL_reverse(idl);
    for (int i = 0; i < DL_size(idl); i++) {
        printf("dl[%d]  = %d\n", i, *(int *) DL_get(idl, i));
    }

    printf("--- Reversing but with empty DynList ---\n");
    DL_clear(idl2);
    DL_reverse(idl2);
    for (int i = 0; i < DL_size(idl2); i++) {
        printf("dl2[%d]  = %d\n", i, *(int *) DL_get(idl2, i));
    }

    printf("--- Setting by index ---\n");
    printf("before:\n");
    for (int i = 1000; i < 1000+num_nums; i++) {
        DL_append(idl2, &i);
    }
    for (int i = 0; i < DL_size(idl2); i++) {
        printf("dl2[%d]  = %d\n", i, *(int *) DL_get(idl2, i));
    }
    int b = 69;
    DL_set(idl2, &b, 0);
    DL_set(idl2, &b, DL_size(idl2)-1);

    printf("after:\n");
    for (int i = 0; i < DL_size(idl2); i++) {
        printf("dl2[%d]  = %d\n", i, *(int *) DL_get(idl2, i));
    }


    printf("--- Couting ---\n");

    printf("occurrences of 69 in dl2: %d\n", DL_count(idl2, &b));
    printf("occurrences of 69 in dl1: %d\n", DL_count(idl, &b));

    int c = 1002;
    int d = 9002;
    printf("index of 69 in dl2: %d\n", DL_index(idl2, &b));
    printf("index of 1002 in dl2: %d\n", DL_index(idl2, &c));
    printf("index of 9002 in dl2: %d\n", DL_index(idl2, &d));

    DL_free(idl);
    DL_free(idl2);


    printf("--- Sorting ---\n");
    DynList *pdl2 = DL_create(4, sizeof(struct Person), compare_people);
    DL_append(pdl2, &p1);
    DL_append(pdl2, &p2);
    DL_append(pdl2, &p3);
    DL_append(pdl2, &p4);
    DL_append(pdl2, &p5);
    DL_append(pdl2, &p6);
    DL_append(pdl2, &p7);
    DL_append(pdl2, &p8);
    DL_append(pdl2, &p9);
    DL_append(pdl2, &p10);
    printf("before:\n");
    for (int i = 0; i < DL_size(pdl2); i++) {
        printPerson(DL_get(pdl2, i));
    }

    DL_sort(pdl2);
    printf("after:\n");

    for (int i = 0; i < DL_size(pdl2); i++) {
        printPerson(DL_get(pdl2, i));
    }


    printf("--- Copying ---\n");

    DynList *cp = DL_copy(pdl2, 0, DL_size(pdl2));
    printf("full copy:\n");
    for (int i = 0; i < DL_size(cp); i++) {
        printPerson(DL_get(cp, i));
    }

    DL_clear(cp);
    cp = DL_copy(pdl2, 3, DL_size(pdl2) - 1);
    printf("original Size=%d\n", DL_size(pdl2));
    printf("cp Size=%d\n", DL_size(cp));
    printf("copy from index 3 to len - 1:\n");
    for (int i = 0; i < DL_size(cp); i++) {
        printPerson(DL_get(cp, i));
    }

    printf("All good!\n");
    return EXIT_SUCCESS;
}


