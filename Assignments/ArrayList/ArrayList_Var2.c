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
#define MAX 10

typedef struct {
    char name[50];
    int age;
} Person;

typedef struct {
    Person elem[MAX];
    int count;
} List;

typedef List* EPtr;

void initialize(EPtr L);
void insertPos(EPtr L, Person data, int position);
void deletePos(EPtr L, int position);
int locate(EPtr L, Person data);
Person retrieve(EPtr L, int position);
void insertSorted(EPtr L, Person data);
void display(EPtr L);
void makeNULL(EPtr L);

int main() {
    List L;
    EPtr ptr = &L;

    initialize(ptr);

    Person p1 = {"Yana", 20};
    Person p2 = {"Rodlie", 21};
    Person p3 = {"Marie", 20};
    Person p4 = {"Angel", 21};
    Person p5 = {"Rayiane", 21};

    insertPos(ptr, p1, 0);
    insertPos(ptr, p2, 1);
    insertPos(ptr, p3, 1);
    printf("After insertPos:\n");
    display(ptr);

    deletePos(ptr, 1);
    printf("After deletePos at 1:\n");
    display(ptr);

    printf("Locate Yana (age 20): index %d\n", locate(ptr, p1));

    Person retrieved = retrieve(ptr, 0);
    printf("Retrieve index 0: Name: %s, Age: %d\n\n", retrieved.name, retrieved.age);

    initialize(ptr);  
    insertSorted(ptr, p4);
    insertSorted(ptr, p5);
    insertSorted(ptr, p1);
    insertSorted(ptr, p2);
    insertSorted(ptr, p3);
    printf("After insertSorted:\n");
    display(ptr);

    makeNULL(ptr);
    printf("After makeNULL:\n");
    display(ptr);

    return 0;
}

void initialize(EPtr L) {
    L->count = 0;
}

void insertPos(EPtr L, Person data, int position) {
    if (L->count == MAX)
        printf("Error: List is full.\n");
    else if (position < 0 || position > L->count)
        printf("Error: Invalid position %d.\n", position);
    else {
        for (int i = L->count; i > position && i >= 0; i--)  
            L->elem[i] = L->elem[i - 1];
        L->elem[position] = data;
        L->count++;
    }
}

void deletePos(EPtr L, int position) {
    if (position < 0 || position >= L->count)
        printf("Error: Invalid position %d.\n", position);
    else {
        for (int i = position; i < L->count - 1 && i >= 0; i++)  
            L->elem[i] = L->elem[i + 1];
        L->count--;
    }
}

int locate(EPtr L, Person data) {
    int result = -1;
    for (int i = 0; i < L->count && result == -1; i++)  
        if (strcmp(L->elem[i].name, data.name) == 0 && L->elem[i].age == data.age)
            result = i;
    return result;
}

Person retrieve(EPtr L, int position) {
    Person result = {"", -1};
    if (position < 0 || position >= L->count)
        printf("Error: Invalid position %d.\n", position);
    else
        result = L->elem[position];
    return result;
}

void insertSorted(EPtr L, Person data) {
    if (L->count == MAX)
        printf("Error: List is full.\n");
    else {
        int i;
        for (i = L->count - 1; i >= 0 && strcmp(L->elem[i].name, data.name) > 0; i--)  
            L->elem[i + 1] = L->elem[i];
        L->elem[i + 1] = data;
        L->count++;
    }
}

void display(EPtr L) {
    for (int i = 0; i < L->count; i++) 
        printf("[%d] Name: %s, Age: %d\n", i, L->elem[i].name, L->elem[i].age);
    printf("\n");
}

void makeNULL(EPtr L) {
    L->count = 0;
}