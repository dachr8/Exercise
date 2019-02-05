///Question #2. Question 10 of Experiment 11 in the Lab Manual (List Sorting)
#include <stdio.h>
#include <malloc.h>

struct list{
    int data;
    struct list *nextPtr;
};

int main(void)
{
    int value;
    struct list *headPtr=NULL,*currentPtr=NULL,*previousPtr=NULL,*tmpPtr=NULL;

    //The establishment of a linked list
    printf("Please input a list(end by -1):");
    scanf("%d",&value);
    while (value!=-1)
    {
        currentPtr=malloc(sizeof(struct list));//Allocate node memory
        if(currentPtr!=NULL)//Insert node
        {
            if(headPtr==NULL)//If you create a head node
                headPtr=currentPtr;
            else
                previousPtr->nextPtr=currentPtr;//link
            currentPtr->data=value;
            previousPtr=currentPtr;
            scanf("%d",&value);
        }
        else
            return 0;
    }
    currentPtr->nextPtr=NULL;//Set the end of the list

    //List Sorting -- Bubble Sort
    for (_Bool flag=1; flag; )
    {
        previousPtr = currentPtr = headPtr;
        flag=0;
        while (currentPtr->nextPtr)
            if (currentPtr->data > currentPtr->nextPtr->data)
            {
                if (currentPtr == headPtr)
                    headPtr = currentPtr->nextPtr;
                else
                    previousPtr->nextPtr = currentPtr->nextPtr;
                tmpPtr = currentPtr->nextPtr->nextPtr;
                currentPtr->nextPtr->nextPtr = currentPtr;
                previousPtr = currentPtr->nextPtr;
                currentPtr->nextPtr = tmpPtr;
                flag=1;
            }
            else
            {
                previousPtr = currentPtr;
                currentPtr = currentPtr->nextPtr;//Point to next node
            }
    }

    printf("The new list is: ");
    currentPtr=headPtr;
    while (currentPtr->nextPtr)
    {
        printf("%d ",currentPtr->data);//Release the current node
        currentPtr=currentPtr->nextPtr;//Point to the next node to be deleted
    }
    printf("%d\n",currentPtr->data);

    //List release
    while (headPtr)
    {
        currentPtr=headPtr;
        headPtr=headPtr->nextPtr;//Point to the next node to be deleted
        free(currentPtr);//Release the current node
    }

    return 0;
}
