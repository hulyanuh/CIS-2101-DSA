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

List initialize(List L);
List insertPos(List L, Person data, int position);
List deletePos(List L, int position);
int locate(List L, Person data);
List insertSorted(List L, Person data);
void display(List L);
List resize(List L);

int main() {
    List L;
    L = initialize(L);

    Person p1 = {"Yana", 20};
    Person p2 = {"Rodlie", 21};
    Person p3 = {"Marie", 20};
    Person p4 = {"Angel", 21};
    Person p5 = {"Rayiane", 21};

    insertPos(L, p1, 0);
    L = insertPos(L, p1, 0);
    L = insertPos(L, p2, 1);
    L = insertPos(L, p3, 1);
    printf("After insertPos (3 elements, max was %d):\n", LENGTH);
    display(L);

    L = insertPos(L, p4, 2);
    printf("After insertPos triggering resize (max now %d):\n", L.max);
    display(L);

    L = deletePos(L, 1);
    printf("After deletePos at 1:\n");
    display(L);

    printf("Locate Yana (age 20): index %d\n\n", locate(L, p1));

    free(L.elem);
    L = initialize(L);
    L = insertSorted(L, p4);
    L = insertSorted(L, p5);
    L = insertSorted(L, p1);
    L = insertSorted(L, p2);
    L = insertSorted(L, p3);
    printf("After insertSorted:\n");
    display(L);

    free(L.elem);
    return 0;
}

List initialize(List L) {
    L.elem = (Person*)malloc(LENGTH * sizeof(Person));
    if (L.elem == NULL)
        printf("Error: Memory allocation failed.\n");
    L.max = LENGTH;
    L.count = 0;
    return L;
}

List resize(List L) {
    Person* newElem = (Person*)realloc(L.elem, L.max * 2 * sizeof(Person));
    if (newElem == NULL)
        printf("Error: Memory reallocation failed.\n");
    else {
        L.elem = newElem;
        L.max *= 2;
        printf("Resized! New max: %d\n", L.max);
    }
    return L;
}

List insertPos(List L, Person data, int position) {
    if (position < 0 || position > L.count)
        printf("Error: Invalid position %d.\n", position);
    else {
        if (L.count == L.max)
            L = resize(L);
        if (L.elem != NULL) {
            for (int i = L.count; i > position && i >= 0; i--)  
                L.elem[i] = L.elem[i - 1];
            L.elem[position] = data;
            L.count++;
        }
    }
    return L;
}

List deletePos(List L, int position) {
    if (position < 0 || position >= L.count)
        printf("Error: Invalid position %d.\n", position);
    else {
        for (int i = position; i < L.count - 1 && i >= 0; i++)  
            L.elem[i] = L.elem[i + 1];
        L.count--;
    }
    return L;
}

int locate(List L, Person data) {
    int result = -1;
    for (int i = 0; i < L.count && result == -1; i++)  
        if (strcmp(L.elem[i].name, data.name) == 0 && L.elem[i].age == data.age)
            result = i;
    return result;
}

List insertSorted(List L, Person data) {
    if (L.count == L.max)
        L = resize(L);
    if (L.elem != NULL) {
        int i;
        for (i = L.count - 1; i >= 0 && strcmp(L.elem[i].name, data.name) > 0; i--)  
            L.elem[i + 1] = L.elem[i];
        L.elem[i + 1] = data;
        L.count++;
    }
    return L;
}

void display(List L) {
    for (int i = 0; i < L.count; i++)  
        printf("[%d] Name: %s, Age: %d\n", i, L.elem[i].name, L.elem[i].age);
    printf("\n");
}