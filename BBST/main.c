#include <stdio.h>
#include <stdlib.h>
#include "bbst.h"

typedef struct {
    size_t id;
    int age;
    float height;
} person_t;

int compare_people(void *a, void *b) {
    return (((person_t *)a)->id - ((person_t *)b)->id);
}

void print_person(person_t *p) {
    printf("----------------------------\n");
    printf("Person:\n");
    printf("id = \t\t%zu\n", p->id);
    printf("age = \t\t%d\n", p->age);
    printf("height = \t%f\n", p->height);
    printf("----------------------------\n");
}

int main() {

    printf("----- BBST -----\n\n");


    BBST *t = BBST_create(sizeof(person_t), compare_people);
    if (t == NULL) {
        printf("Creation of BBST failed.\n");
        return 1;
    }
    printf("BBST created successfully.\n");

    person_t p0 = {
        .id = 0,
        .age = 21,
        .height = 1.76,
    };
    person_t p1 = {
        .id = 1,
        .age = 23,
        .height = 1.86,
    };
    person_t p2 = {
        .id = 2,
        .age = 25,
        .height = 1.80,
    };
    BBST_insert(t, &p0);
    BBST_insert(t, &p1);
    BBST_insert(t, &p1);
    BBST_insert(t, &p2);

    print_person(t->root->data);
    print_person(t->root->right->data);
    print_person(t->root->right->left->data);
    print_person(t->root->right->right->data);

    BBST_free(t);
    printf("BBST freed successfully.\n");

    return EXIT_SUCCESS;
}
