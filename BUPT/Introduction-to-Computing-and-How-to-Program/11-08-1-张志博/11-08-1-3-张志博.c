///Question #3. Question 13 of Experiment 11 in the Lab Manual
#include <stdio.h>
#include <malloc.h>

struct list{
    int data;
    struct list *nextPtr;
};

int main(void)
{
    int value,s[2],t[2];
    struct list *headPtr=NULL,*currentPtr=NULL,*previousPtr=NULL,*tmpPtr=NULL,*preSPtr[2]={NULL,NULL},*TPtr[2]={NULL,NULL};

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

    //Get s1,t1,s2,t2
    printf("Please input four integers: ");
    scanf("%d%d%d%d",&s[0],&t[0],&s[1],&t[1]);//s1 <= t1 < s2 <= t2

    //Find the node before s and the node t
    currentPtr=headPtr;
    for (int i = 1, j = 0; j < 2; i++) {
        if(i==t[j])
        {
            TPtr[j]=currentPtr;//Find the node t
            j++;
        }
        if(i==s[j]-1)
            preSPtr[j]=currentPtr;//Find the node before s
        currentPtr=currentPtr->nextPtr;//Point to next node
    }

    //Linked list node exchange
    if(s[0]==1)//If s1 == 1, then preSPtr[0] == NULL, so let headPtr instead of it.
    {
        tmpPtr=headPtr;
        headPtr=preSPtr[1]->nextPtr;
    }
    else
    {
        tmpPtr=preSPtr[0]->nextPtr;             //tmp -> s1
        preSPtr[0]->nextPtr=preSPtr[1]->nextPtr;//preS1->nextPtr -> s2
    }
    if(t[0]+1!=s[1])//If t1 + 1 != s1, then there is a node between s1-t1 and s2-t2 at least.
    {
        preSPtr[1]->nextPtr=tmpPtr;             //preS2->nextPtr -> s1
        tmpPtr=TPtr[0]->nextPtr;                //tmp -> t1->next
    }
    TPtr[0]->nextPtr=TPtr[1]->nextPtr;          //t1->next -> t2->next
    TPtr[1]->nextPtr=tmpPtr;                    //t2->next -> t1->next


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
