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
    Person p2 = {"Marie", 20};
    Person p3 = {"Rodlie", 21};
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
    printf("After insertSorted:\n");
    display(L);

    return 0;
}

List initialize(List L){
    L.count = 0;
    return L;
}

List insertPos(List L, Person data, int position){
    if(L.count == MAX)
        printf("Error: List is full!\n");
    else if(position < 0 || position > L.count)
        printf("Error: Invalid position %d!\n");
    else {
        for(int i = L.count; i > position && i >= 0; i--)
            L.elem[i] = L.elem[i - 1];
        L.elem[position] = data;
        L.count++;
    }
    return L;
}

List deletePos(List L, int position){
    if(position < 0 || position >= L.count)
        printf("Error: Invalid position %d.\n", position);
    else {
        for(int i = position; i < L.count - 1 && i >= 0; i++)
            L.elem[i] = L.elem[i + 1];
        L.count--;
    }
    return L;
}

int locate(List L, Person data){
    int result = -1;
    
    for(int i = 0; i < L.count && result == -1; i++){
        if(strcmp(L.elem[i].name, data.name) == 0 && L.elem[i].age == data.age)
            result = i;
        return result;
    }
}

List insertSorted(List L, Person data){
    if(L.count == MAX)
        printf("Error: List is full!\n");
    else {
        int i;
        for(i = L.count - 1; i >= 0 && strcmp(L.elem[i].name, data.name) > 0; i--)
            L.elem[i + 1] = L.elem[i];
        L.elem[i + 1] = data;
        L.count++;
    }
    return L;
}

void display(List L){
    for(int i = 0; i < L.count; i++)
        printf("[%d] Name: %s, Age: %d\n", i, L.elem[i].name, L.elem[i].age);
    printf("\n");
}