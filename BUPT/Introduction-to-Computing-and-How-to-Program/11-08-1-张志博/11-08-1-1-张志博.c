//Question #1. Question 4 of Experiment 11 in the Lab Manual (Creation, Search, and Release of Lists)
#include <stdio.h>
#include <malloc.h>

struct list{
    int data;
    struct list *nextPtr;
};

int main(void)
{
    int value,max,min,total=0;
    struct list *headPtr=NULL,*currentPtr=NULL,*previousPtr=NULL;

    //The establishment of a linked list
    printf("Please input a series of integers(end by -1):");
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

    //List lookup
    max=min=headPtr->data;
    currentPtr=headPtr;
    while (currentPtr)
    {
        value=currentPtr->data;
        max=max>value?max:value;
        min=min<value?min:value;
        total+=value;
        currentPtr=currentPtr->nextPtr;//Point to next node
    }

    printf("The maximum, minimum and the total are: %d %d %d",max,min,total);

    //List release
    while (headPtr)
    {
        currentPtr=headPtr;
        headPtr=headPtr->nextPtr;//Point to the next node to be deleted
        free(currentPtr);//Release the current node
    }

    return 0;
}
