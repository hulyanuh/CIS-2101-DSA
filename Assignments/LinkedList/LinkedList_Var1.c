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

List initialize(List L);
List insertPos(List L, Person data, int position);
List deletePos(List L, int position);
int locate(List L, Person data);
List insertSorted(List L, Person data);
void display(List L);

int main() {
    List L;
    L = initialize(L);

    Person p1 = {"Yana", 20};
    Person p2 = {"Rodlie", 21};
    Person p3 = {"Marie", 20};
    Person p4 = {"Angel", 21};
    Person p5 = {"Rayiane", 21};

    L = insertPos(L, p1, 0);
    L = insertPos(L, p2, 1);
    L = insertPos(L, p3, 1);
    printf("After insertPos:\n");
    display(L);

    L = deletePos(L, 1);
    printf("After deletePos at 1:\n");
    display(L);

    printf("Locate Yana (age 20): index %d\n\n", locate(L, p1));

    L = initialize(L);
    L = insertSorted(L, p4);
    L = insertSorted(L, p5);
    L = insertSorted(L, p1);
    L = insertSorted(L, p2);
    L = insertSorted(L, p3);
    printf("After insertSorted:\n");
    display(L);

    return 0;
}

List initialize(List L) {
    L.head = NULL;
    L.count = 0;
    return L;
}

List insertPos(List L, Person data, int position) {
    if (position < 0 || position > L.count)
        printf("Error: Invalid position %d.\n", position);
    else {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL)
            printf("Error: Memory allocation failed.\n");
        else {
            newNode->data = data;
            newNode->next = NULL;

            if (position == 0) {
                newNode->next = L.head;
                L.head = newNode;
            } else {
                Node* curr = L.head;
                for (int i = 0; i < position - 1 && curr != NULL; i++)  
                    curr = curr->next;

                if (curr == NULL)
                    printf("Error: Position out of bounds.\n");
                else {
                    newNode->next = curr->next;
                    curr->next = newNode;
                }
            }
            L.count++;
        }
    }
    return L;
}

List deletePos(List L, int position) {
    if (position < 0 || position >= L.count)
        printf("Error: Invalid position %d.\n", position);
    else {
        Node* toDelete = NULL;

        if (position == 0) {
            toDelete = L.head;
            L.head = L.head->next;
        } else {
            Node* curr = L.head;
            for (int i = 0; i < position - 1 && curr != NULL; i++)  
                curr = curr->next;

            if (curr == NULL || curr->next == NULL)
                printf("Error: Position out of bounds.\n");
            else {
                toDelete = curr->next;
                curr->next = toDelete->next;
            }
        }

        if (toDelete != NULL) {
            free(toDelete);
            L.count--;
        }
    }
    return L;
}

int locate(List L, Person data) {
    int result = -1;
    Node* curr = L.head;
    for (int i = 0; curr != NULL && result == -1; i++) {  
        if (strcmp(curr->data.name, data.name) == 0 && curr->data.age == data.age)
            result = i;
        curr = curr->next;
    }
    return result;
}

List insertSorted(List L, Person data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
        printf("Error: Memory allocation failed.\n");
    else {
        newNode->data = data;
        newNode->next = NULL;

        if (L.head == NULL || strcmp(data.name, L.head->data.name) <= 0) {
            newNode->next = L.head;
            L.head = newNode;
        } else {
            Node* curr = L.head;
            for ( ; curr->next != NULL && strcmp(curr->next->data.name, data.name) <= 0; curr = curr->next);
            newNode->next = curr->next;
            curr->next = newNode;
        }
        L.count++;
    }
    return L;
}

void display(List L) {
    Node* curr = L.head;
    for (int i = 0; curr != NULL; i++) {
        printf("[%d] Name: %s, Age: %d\n", i, curr->data.name, curr->data.age);
        curr = curr->next;
    }
    printf("\n");
}