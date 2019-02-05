//use_q.c -- Driver test Queue interface
//Compile with queue.c

#include <stdio.h>
#include "queue.h"


int main(void) {
	Queue line;
	Item tmp;
	char ch;

	InitializeQueue(&line);
	puts("Testing the Queue interface. Type a to add a value,");
	puts("type d to delete a value, and type q to quit.");
	while ((ch = getchar()) != 'q') {
		if (ch == 'a') {
			printf("Integer to add: ");
			scanf("%d", &tmp);
			if (QueueIsFull(&line))
				puts("Queue is full!");
			else {
				printf("Putting %d into queue\n", tmp);
				EnQueue(tmp, &line);
			}
		} else if (ch == 'd') {
			if (QueueIsEmpty(&line))
				puts("Nothing to delete!");
			else {
				printf("Removing %d from queue\n", tmp);
				DeQueue(&tmp, &line);
			}
		}
		if (ch == 'a' || ch == 'd') {
			printf("%d items in queue\n", QueueItemCount(&line));
			puts("Type a to add, d to delete, q to quit:");
		}
	}
	EmptyTheQueue(&line);
	puts("Bye!");

	return 0;
}
