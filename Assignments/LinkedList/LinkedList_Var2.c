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

typedef struct {
    char name[50];
    int age;
} Person;

typedef struct Node {
    Person data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} List;

List* initialize();
void empty(List* list);
void insertFirst(List* list, Person data);
void insertLast(List* list, Person data);
void insertPos(List* list, Person data, int index);
void deleteStart(List* list);
void deleteLast(List* list);
void deletePos(List* list, int index);
Person retrieve(List* list, int index);
int locate(List* list, Person data);
void display(List* list);

int main() {
    List* list = initialize();
    if (list == NULL) return 1;

    Person p1 = {"Yana", 20};
    Person p2 = {"Rodlie", 21};
    Person p3 = {"Marie", 20};
    Person p4 = {"Angel", 21};
    Person p5 = {"Rayiane", 21};

    insertFirst(list, p2);
    insertFirst(list, p1);
    printf("After insertFirst (p1, p2):\n");
    display(list);

    insertLast(list, p3);
    printf("After insertLast (p3):\n");
    display(list);

    insertPos(list, p4, 1);
    printf("After insertPos (p4 at index 1):\n");
    display(list);

    deleteStart(list);
    printf("After deleteStart:\n");
    display(list);

    deleteLast(list);
    printf("After deleteLast:\n");
    display(list);

    deletePos(list, 1);
    printf("After deletePos at index 1:\n");
    display(list);

    insertLast(list, p4);
    insertLast(list, p5);
    Person retrieved = retrieve(list, 1);
    printf("Retrieved index 1: Name: %s, Age: %d\n\n", retrieved.name, retrieved.age);

    printf("Locate Rayiane (age 21): index %d\n\n", locate(list, p5));

    empty(list);
    printf("After empty:\n");
    display(list);

    free(list);  
    return 0;
}

List* initialize() {
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL)
        printf("Error: Memory allocation failed.\n");
    else {
        list->head = NULL;
        list->count = 0;
    }
    return list;
}

void empty(List* list) {
    Node* current = list->head;
    while (current != NULL && list->count > 0) {  
        Node* toFree = current;
        current = current->next;
        free(toFree);
        list->count--;
    }
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List* list, Person data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
        printf("Error: Memory allocation failed.\n");
    else {
        newNode->data = data;
        newNode->next = list->head;
        list->head = newNode;
        list->count++;
    }
}

void insertLast(List* list, Person data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
        printf("Error: Memory allocation failed.\n");
    else {
        newNode->data = data;
        newNode->next = NULL;
        if (list->head == NULL)
            list->head = newNode;
        else {
            Node* current = list->head;
            for ( ; current->next != NULL && current != NULL; current = current->next);
            current->next = newNode;
        }
        list->count++;
    }
}

void insertPos(List* list, Person data, int index) {
    if (index < 0 || index > list->count)
        printf("Error: Invalid index %d.\n", index);
    else if (index == 0)
        insertFirst(list, data);
    else if (index == list->count)
        insertLast(list, data);
    else {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL)
            printf("Error: Memory allocation failed.\n");
        else {
            newNode->data = data;
            Node* current = list->head;
            for (int i = 0; i < index - 1 && current != NULL; i++)  
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
            list->count++;
        }
    }
}

void deleteStart(List* list) {
    if (list->head == NULL)
        printf("Error: List is empty.\n");
    else {
        Node* current = list->head;
        list->head = current->next;
        free(current);
        list->count--;
    }
}

void deleteLast(List* list) {
    if (list->head == NULL)
        printf("Error: List is empty.\n");
    else if (list->count == 1) {
        free(list->head);
        list->head = NULL;
        list->count--;
    } else {
        Node* current = list->head;
        for (int i = 0; i < list->count - 2 && current->next != NULL; i++)  
            current = current->next;
        free(current->next);
        current->next = NULL;
        list->count--;
    }
}

void deletePos(List* list, int index) {
    if (index < 0 || index >= list->count)
        printf("Error: Invalid index %d.\n", index);
    else if (index == 0)
        deleteStart(list);
    else {
        Node* current = list->head;
        for (int i = 0; i < index - 1 && current != NULL; i++)  
            current = current->next;
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
        list->count--;
    }
}

Person retrieve(List* list, int index) {
    Person result = {"", -1};
    if (index < 0 || index >= list->count)
        printf("Error: Invalid index %d.\n", index);
    else {
        Node* current = list->head;
        for (int i = 0; i < index && current != NULL; i++)  
            current = current->next;
        result = current->data;
    }
    return result;
}

int locate(List* list, Person data) {
    int result = -1;
    if (list->head == NULL)
        printf("Error: List is empty.\n");
    else {
        Node* current = list->head;
        for (int i = 0; current != NULL && result == -1; i++) {  
            if (strcmp(current->data.name, data.name) == 0 && current->data.age == data.age)
                result = i;
            current = current->next;
        }
    }
    return result;
}

void display(List* list) {
    Node* current = list->head;
    for (int i = 0; current != NULL; i++) { 
        printf("[%d] Name: %s, Age: %d\n", i, current->data.name, current->data.age);
        current = current->next;
    }
    printf("\n");
}