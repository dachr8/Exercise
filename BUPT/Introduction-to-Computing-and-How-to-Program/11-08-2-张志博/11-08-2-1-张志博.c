//Question #1. Question 9 of Experiment 11 in the Lab Manual（List merging）
#include <stdio.h>
#include <malloc.h>

typedef struct list {
    int data;
    struct list *nextPtr;
} *LISTPTR;

int main(void) {
    int value;
    LISTPTR headPtr[2] = {NULL, NULL}, tmpPtr = NULL, current[2] = {NULL, NULL};

    //The establishment of a linked list
    for (int i = 0; i < 2; ++i) {
        printf("Please input the elements of list %c(end by -1):", 'A' + i);
        scanf("%d", &value);
        current[i] = headPtr[i] = malloc(sizeof(struct list));//Allocate node memory
        while (value != -1) {
            current[i]->nextPtr = malloc(sizeof(struct list));//Allocate node memory
            current[i]->nextPtr->data = value;
            current[i] = current[i]->nextPtr;//Point to next node
            scanf("%d", &value);
        }
        current[i]->nextPtr = NULL;//Set the end of the list
    }

    //List merging
    if (headPtr[1]->nextPtr) {
        current[0] = headPtr[0];
        current[1] = headPtr[1];
        while (current[0]->nextPtr && current[1]->nextPtr)
            if (current[1] && current[0]->nextPtr->data > current[1]->nextPtr->data) {
                tmpPtr = current[0]->nextPtr;
                current[0]->nextPtr = current[1]->nextPtr;
                current[1]->nextPtr = current[1]->nextPtr->nextPtr;
                current[0]->nextPtr->nextPtr = tmpPtr;
            } else if (current[0]->nextPtr->data == current[1]->nextPtr->data)
                current[1] = current[1]->nextPtr;
            else
                current[0] = current[0]->nextPtr;

        while (current[1]->nextPtr) {
            current[0]->nextPtr = current[1]->nextPtr;
            current[1]->nextPtr = current[1]->nextPtr->nextPtr;
            current[0]->nextPtr->nextPtr = NULL;
            current[0] = current[0]->nextPtr;
        }
    }


    //Show the new lists
    for (int i = 0; i < 2; ++i) {
        if (!headPtr[i]->nextPtr)
            printf("There is no item in %c list.\n", 'A' + i);
        else {
            printf("The new list %c is: ", 'A' + i);
            tmpPtr = headPtr[i]->nextPtr;
            while (tmpPtr->nextPtr) {
                printf("%d ", tmpPtr->data);
                tmpPtr = tmpPtr->nextPtr;//Point to the next node
            }
            printf("%d\n", tmpPtr->data);
        }
    }

    //List release
    for (int i = 0; i < 2; ++i)
        while (headPtr[i]) {
            tmpPtr = headPtr[i];
            headPtr[i] = headPtr[i]->nextPtr;//Point to the next node to be deleted
            free(tmpPtr);//Release the current node
        }

    return 0;
}
