// BuddySystem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buddy.h"
#define MOM_SIZE 4096
#define MAX_USE_TIME 64
#define REQ_LEN 1000

typedef enum CMD {
	ALLOC, FREE, NONE
}CMD;

typedef struct Request {
	CMD cmd;
	int size;
	int loc;
}Request;

int main(void) {
	//* seq mode
	struct Buddy* buddy = buddy_new(MOM_SIZE);

	srand((unsigned int)time(NULL));
	for (int k = 64; k <= MOM_SIZE; k <<= 1) {
		printf("Memory size: %dB \t Maximum size of memory requested each time: %dB\n", MOM_SIZE, k);

		int used_size = 0;              // used memory size
		int maf_times = 0;              // times of failing to applicate memory
		int maf_p_times = 0;            // times of failing to applicate memory due to fragmentation
		Request requests[REQ_LEN * 2];  // request of memory allocation and free

		for (int i = 0; i < REQ_LEN * 2; ++i) {
			requests[i].cmd = NONE;
		}
		for (int i = 0; i < REQ_LEN * 2; ++i) {
			switch (requests[i].cmd) {
				case NONE:
					requests[i].cmd = ALLOC;
					requests[i].size = rand() % k + 1;

					int j = rand() % MAX_USE_TIME + 1;
					if (i + j >= REQ_LEN * 2) {
						j = 1;
					}
					while (requests[i + j].cmd != 2) {
						if (i + j >= REQ_LEN * 2) {
							j = 1;
						} else {
							++j;
						}
					}
					requests[i + j].cmd = FREE;
					requests[i + j].size = requests[i].size;
					requests[i + j].loc = requests[i].loc = buddy_alloc(buddy, requests[i].size);

					//printf("alloc: %d->%d\n", requests[i].size, requests[i].loc);
					if (requests[i].loc == -1) {
						//printf("allocation failure: %d \t used size: %d \t memory size: %d \n", requests[i].size, used_size, MOM_SIZE);
						//buddy_print(buddy);
						++maf_times;
						if (requests[i].size < MOM_SIZE - used_size) {
							//printf("allocation failure: %d \t used size: %d \t memory size: %d \n", requests[i].size, used_size, MOM_SIZE);
							++maf_p_times;
						}
					} else {
						used_size += requests[i].size;
					}
					break;
				case FREE:
					//printf("free: %d\n", requests[i].arg);	
					if (requests[i].loc != -1) {
						buddy_free(buddy, requests[i].loc);
						used_size -= requests[i].size;
					}
					break;
				default:
					break;
			}
		}
		printf("Probability of failing to applicate memory: %.1lf%%\n", (double)100 * maf_times / REQ_LEN);
		printf("Probability of failing to applicate memory due to fragmentation: %.1lf%%\n\n", (double)100 * maf_p_times / REQ_LEN);
	}
	//*/

	/* cmd mode
	struct Buddy* buddy = buddy_new(MOM_SIZE);
	char cmd[8];
	int arg;
	buddy_print(buddy);
	while (1) {
		scanf_s("%s", cmd, 8);
		scanf_s("%d", &arg);
		if (strcmp(cmd, "alloc") == 0) {
			printf("allocated@%d\n", buddy_alloc(buddy, arg));
			buddy_print(buddy);
		} else if (strcmp(cmd, "free") == 0) {
			buddy_free(buddy, arg);
			buddy_print(buddy);
		} else if (strcmp(cmd, "size") == 0) {
			printf("size: %d\n", buddy_size(buddy, arg));
			buddy_print(buddy);
		} else {
			buddy_print(buddy);
		}
	}
	//*/

	return 0;
}

