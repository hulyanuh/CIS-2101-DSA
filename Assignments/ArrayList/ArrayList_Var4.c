/* 
INSTRUCTIONS:
Using the ADT GuideLinks to an external site., practice coding all of the operations of the LIST with the following rules:
> Use only one return statement
> No unnecessary break statements
> Use of the 2 loop conditions, (when it will end && when it should end)
> Apply error-catching statements
Challenge: use a person structure instead of just integers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 3 

typedef struct {
    char name[50];
    int age;
} Person;

typedef struct {
    Person* elem;  
    int count;
    int max;
} List;

void initialize(List* L);
void insertPos(List* L, Person data, int position);
void deletePos(List* L, int position);
int locate(List* L, Person data);
Person retrieve(List* L, int position);
void insertSorted(List* L, Person data);
void display(List* L);
void resize(List* L);
void makeNULL(List* L);

int main() {
    List L;
    initialize(&L);

    Person p1 = {"Yana", 20};
    Person p2 = {"Rodlie", 21};
    Person p3 = {"Marie", 20};
    Person p4 = {"Angel", 21};
    Person p5 = {"Rayiane", 21};

    insertPos(&L, p1, 0);
    insertPos(&L, p2, 1);
    insertPos(&L, p3, 1);
    printf("After insertPos (3 elements, max was %d):\n", LENGTH);
    display(&L);

    insertPos(&L, p4, 2);
    printf("After insertPos triggering resize (max now %d):\n", L.max);
    display(&L);

    deletePos(&L, 1);
    printf("After deletePos at 1:\n");
    display(&L);

    printf("Locate Yana (age 20): index %d\n", locate(&L, p1));

    Person retrieved = retrieve(&L, 0);
    printf("Retrieve index 0: Name: %s, Age: %d\n\n", retrieved.name, retrieved.age);

    makeNULL(&L);
    initialize(&L);
    insertSorted(&L, p4);
    insertSorted(&L, p5);
    insertSorted(&L, p1);
    insertSorted(&L, p2);
    insertSorted(&L, p3);
    printf("After insertSorted:\n");
    display(&L);

    makeNULL(&L); 
    return 0;
}

void initialize(List* L) {
    L->elem = (Person*)malloc(LENGTH * sizeof(Person));
    if (L->elem == NULL)
        printf("Error: Memory allocation failed.\n");
    L->max = LENGTH;
    L->count = 0;
}

void resize(List* L) {
    Person* newElem = (Person*)realloc(L->elem, L->max * 2 * sizeof(Person));
    if (newElem == NULL)
        printf("Error: Memory reallocation failed.\n");
    else {
        L->elem = newElem;
        L->max *= 2;
        printf("Resized! New max: %d\n", L->max);
    }
}

void insertPos(List* L, Person data, int position) {
    if (position < 0 || position > L->count)
        printf("Error: Invalid position %d.\n", position);
    else {
        if (L->count == L->max)
            resize(L);
        if (L->elem != NULL) {
            for (int i = L->count; i > position && i >= 0; i--)  
                L->elem[i] = L->elem[i - 1];
            L->elem[position] = data;
            L->count++;
        }
    }
}

void deletePos(List* L, int position) {
    if (position < 0 || position >= L->count)
        printf("Error: Invalid position %d.\n", position);
    else {
        for (int i = position; i < L->count - 1 && i >= 0; i++)  
        L->count--;
    }
}

int locate(List* L, Person data) {
    int result = -1;
    for (int i = 0; i < L->count && result == -1; i++)  
        if (strcmp(L->elem[i].name, data.name) == 0 && L->elem[i].age == data.age)
            result = i;
    return result;
}

Person retrieve(List* L, int position) {
    Person result = {"", -1};
    if (position < 0 || position >= L->count)
        printf("Error: Invalid position %d.\n", position);
    else
        result = L->elem[position];
    return result;
}

void insertSorted(List* L, Person data) {
    if (L->count == L->max)
        resize(L);
    if (L->elem != NULL) {
        int i;
        for (i = L->count - 1; i >= 0 && strcmp(L->elem[i].name, data.name) > 0; i--)  
            L->elem[i + 1] = L->elem[i];
        L->elem[i + 1] = data;
        L->count++;
    }
}

void display(List* L) {
    for (int i = 0; i < L->count; i++)  
        printf("[%d] Name: %s, Age: %d\n", i, L->elem[i].name, L->elem[i].age);
    printf("\n");
}

void makeNULL(List* L) {
    free(L->elem);
    L->elem = NULL;
    L->count = 0;
    L->max = 0;
}