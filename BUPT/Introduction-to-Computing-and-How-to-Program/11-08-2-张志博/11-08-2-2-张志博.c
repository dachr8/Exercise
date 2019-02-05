//Question #2. Question 15 of Experiment 11 in the Lab Manual（Split list）
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct list {
    char data;
    struct list *nextPtr;
} *LISTPTR;

int main(void) {
    int type;
    char value[2];
    LISTPTR headPtr[4] = {NULL, NULL, NULL, NULL}, currentPtr[4] = {NULL, NULL, NULL, NULL};
    LISTPTR tmpPtr = NULL, tmp2Ptr = NULL;

    //The establishment of a linked list
    for (int i = 0; i < 4; ++i)
        currentPtr[i] = headPtr[i] = malloc(sizeof(struct list));//Allocate node memory
    printf("Please input the elements of list(end by -1):");
    scanf("%s", value);
    while (value[0] != '-' && value[1] != '1') {
        currentPtr[0]->nextPtr = malloc(sizeof(struct list));//Allocate node memory
        currentPtr[0]->nextPtr->data = value[0];
        currentPtr[0] = currentPtr[0]->nextPtr;//Point to next node
        scanf("%s", value);
    }
    getchar();
    currentPtr[0]->nextPtr = NULL;//Set the end of the list


    //List Sorting -- Bubble Sort
    for (_Bool flag = 1; flag;) {
        currentPtr[0] = headPtr[0];
        flag = 0;
        while (currentPtr[0]->nextPtr->nextPtr)
            if (currentPtr[0]->nextPtr->data > currentPtr[0]->nextPtr->nextPtr->data) {
                tmpPtr = currentPtr[0]->nextPtr;
                tmp2Ptr = currentPtr[0]->nextPtr->nextPtr->nextPtr;
                currentPtr[0]->nextPtr = currentPtr[0]->nextPtr->nextPtr;
                currentPtr[0]->nextPtr->nextPtr = tmpPtr;
                tmpPtr->nextPtr = tmp2Ptr;
                flag = 1;
            } else
                currentPtr[0] = currentPtr[0]->nextPtr;//Point to next node
    }

    //Split list
    currentPtr[0] = headPtr[0];
    while (currentPtr[0]->nextPtr) {
        if (isalpha(currentPtr[0]->nextPtr->data))
            type = 1;
        else if (isdigit(currentPtr[0]->nextPtr->data))
            type = 2;
        else
            type = 3;
        currentPtr[type]->nextPtr = malloc(sizeof(struct list));//Allocate node memory
        currentPtr[type]->nextPtr = currentPtr[0]->nextPtr;//link
        tmpPtr = currentPtr[0]->nextPtr->nextPtr;
        currentPtr[type] = currentPtr[type]->nextPtr;//Point to the next node
        currentPtr[type]->nextPtr = NULL;//Set the end of the list
        currentPtr[0]->nextPtr = tmpPtr;//Point to the next node
    }


    //Show the new lists
    for (int i = 1; i < 4; ++i) {
        if (!headPtr[i]->nextPtr)
            printf("There is no item in %c list.\n", 'A' + i - 1);
        else {
            printf("The list %c is: ", 'A' + i - 1);
            currentPtr[0] = headPtr[i]->nextPtr;
            while (currentPtr[0]->nextPtr) {
                printf("%c ", currentPtr[0]->data);
                currentPtr[0] = currentPtr[0]->nextPtr;//Point to the next node
            }
            printf("%c\n", currentPtr[0]->data);
        }
    }

    //List release
    for (int i = 0; i < 4; ++i)
        while (headPtr[i]) {
            currentPtr[0] = headPtr[i];
            headPtr[i] = headPtr[i]->nextPtr;//Point to the next node to be deleted
            free(currentPtr);//Release the current node
        }

    return 0;
}
