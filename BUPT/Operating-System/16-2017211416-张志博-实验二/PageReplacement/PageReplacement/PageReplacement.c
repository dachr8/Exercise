#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INVALID -1
#define INS_NUM 16384            // 指令数量 16K=16*1024=16384
#define PHYSICAL_PAGE_SIZE 4096  // 物理页面大小 4KB=4096
#define MAX_PAGE_NUM 64          // 最大虚拟内存页数 64
#define PAGE_NUM 28              // 物理内存页数 1-28

typedef struct {
	int pfn;      // 面号
	int counter;  // 一个周期内访问该页面的次数 / 访问时间
}pl_type;

typedef struct pfc_struct {      //页面控制结构
	int pn, pfn;
	struct pfc_struct* next;
} pfc_type;

pl_type pl[PAGE_NUM];    //页面结构数组
pfc_type pfc[PAGE_NUM], * freepf_head;
int page[INS_NUM];


/*
  Name:  void  initialize(int total_pf)
  Achieve:初始化相关数据结构
*/
void initialize(int total_pf) {
	for (int i = 0; i < PAGE_NUM; ++i) {
		pl[i].pfn = INVALID;  // 置页面控制结构中的页号，页面为空
		pl[i].counter = 0;    // 页面控制结构中的访问次数为0
	}
	for (int i = 0; i < total_pf - 1; ++i) {
		pfc[i].next = &pfc[i + 1];
		pfc[i].pfn = i;  // 建立pfc[i]和pfc[i+1]之间的连接
	}
	pfc[total_pf - 1].next = NULL;
	pfc[total_pf - 1].pfn = total_pf - 1;
	freepf_head = &pfc[0];  // 页面队列的头指针为pfc[0]
}


// Optimal
double OPT(int total_pf) {
	int pf_times = 0;
	int maxpage, dist[PAGE_NUM];
	initialize(total_pf);
	for (int i = 0; i < INS_NUM; i++) {
		// 页面失效
		if (pl[page[i]].pfn == INVALID) {
			++pf_times;
			// 无空闲页面
			if (freepf_head == NULL) {
				for (int j = 0; j < PAGE_NUM; ++j) {
					if (pl[j].pfn == INVALID) {
						dist[j] = 0;
					} else {
						dist[j] = INT_MAX;
					}
				}
				for (int j = 0; j < PAGE_NUM; ++j) {
					if ((pl[j].pfn != INVALID) && (dist[j] == 32767)) {
						dist[j] = j;
					}
				}
				int max = 0;
				for (int j = 0; j < PAGE_NUM; ++j)
					if (max < dist[j]) {
						max = dist[j];
						maxpage = j;
					}
				freepf_head = &pfc[pl[maxpage].pfn];
				freepf_head->next = NULL;
				pl[maxpage].pfn = INVALID;
			}
			pl[page[i]].pfn = freepf_head->pfn;
			freepf_head = freepf_head->next;
		}
	}
	return 1 - (double)pf_times / INS_NUM;
}


// Fisrt In First Out
double FIFO(int total_pf) {
	int pf_times = 0;
	pfc_type* busypf_head = NULL;
	pfc_type* busypf_tail = NULL;
	initialize(total_pf); //初始化相关页面控制用数据结构

	for (int i = 0; i < INS_NUM; ++i) {
		//页面失效
		if (pl[page[i]].pfn == INVALID) {
			++pf_times;  //失效次数
			//无空闲页面
			if (freepf_head == NULL && busypf_head) {
				pfc_type* tmp = busypf_head->next;
				pl[busypf_head->pn].pfn = INVALID;
				freepf_head = busypf_head;  //释放忙页面队列的第一个页面
				busypf_head->next = NULL;  //表明还是缺页
				busypf_head = tmp;
			}
			if (freepf_head) {
				pfc_type* tmp = freepf_head->next;
				freepf_head->pn = page[i];
				pl[page[i]].pfn = freepf_head->pfn;
				freepf_head->next = NULL; //使busy的尾为null
				if (busypf_tail) {
					busypf_tail->next = freepf_head;
					busypf_tail = freepf_head;
				} else {
					busypf_tail = busypf_head = freepf_head;
				}
				freepf_head = tmp;
			}
		}
	}
	return 1 - (double)pf_times / INS_NUM;
}

// Least Recently Used
double LRU(int total_pf) {
	int pf_times = 0;
	int minj;
	int present_time = 1;
	initialize(total_pf);
	for (int i = 0; i < INS_NUM; ++i) {
		//页面失效
		if (pl[page[i]].pfn == INVALID) {
			++pf_times;
			//无空闲页面
			if (freepf_head == NULL) {
				int min = INT_MAX;//设置最大值
				 //找出time的最小值
				for (int j = 0; j < PAGE_NUM; ++j) {
					if (min > pl[j].counter&& pl[j].pfn != INVALID) {
						min = pl[j].counter;
						minj = j;
					}
				}
				freepf_head = &pfc[pl[minj].pfn];  // 空出一个单元
				pl[minj].pfn = INVALID;
				pl[minj].counter = 1;
				freepf_head->next = NULL;
			}
			pl[page[i]].pfn = freepf_head->pfn;  // 有空闲页面,改为有效
			pl[page[i]].counter = present_time;
			freepf_head = freepf_head->next; // 减少一个free 页面
		} else {
			pl[page[i]].counter = present_time;  // 命中则增加该单元的访问次数
			++present_time;
		}
	}
	return 1 - (double)pf_times / INS_NUM;
}


// Least Frequently Used
double LFU(int total_pf) {
	int pf_times = 0;
	int minj;
	initialize(total_pf);
	for (int i = 0; i < INS_NUM; ++i) {
		//页面失效
		if (pl[page[i]].pfn == INVALID) {
			++pf_times;
			//无空闲页面
			if (freepf_head == NULL) {
				int min = INT_MAX;
				//获取counter的使用用频率最小的内存	
				for (int j = 0; j < PAGE_NUM; ++j) {
					if (min > pl[j].counter&& pl[j].pfn != INVALID) {
						min = pl[j].counter;
						minj = j;
					}
				}
				freepf_head = &pfc[pl[minj].pfn];
				pl[minj].pfn = INVALID;
				pl[minj].counter = 0;
				freepf_head->next = NULL;
			}
			pl[page[i]].pfn = freepf_head->pfn;  // 有空闲页面,改为有效
			freepf_head = freepf_head->next;  // 减少一个free 页面
		}
		pl[page[i]].counter++;
	}
	return 1 - (double)pf_times / INS_NUM;
}

int main(void) {
	srand((int)time(NULL));

	// 产生指令队列
	int ins[INS_NUM];
	ins[0] = 0;
	double tmp_sum = 0;
	for (int i = 1; i < INS_NUM; ++i) {
		double tmp = (double)rand() / RAND_MAX;
		double tmp2 = 0;
		if (tmp < 0.7) {
			ins[i] = ins[i - 1] + 16;  // 顺序执行一条指令
		} else if (tmp < 0.8) {
			tmp2 = (tmp - 0.7) / 0.1;
			if (tmp2 < 0.8) {
				ins[i] = ins[i - 1] - PHYSICAL_PAGE_SIZE - 16 * (rand() % (PHYSICAL_PAGE_SIZE / 16 * 2));  // 执行前12地址指令
			} else if (tmp2 < 0.95) {
				ins[i] = ins[i - 1] - PHYSICAL_PAGE_SIZE * 3 - 16 * (rand() % (PHYSICAL_PAGE_SIZE / 16 * 2));  // 执行前34地址指令
			} else {
				ins[i] = ins[i - 1] - PHYSICAL_PAGE_SIZE * 5 - 16 * (rand() % (PHYSICAL_PAGE_SIZE / 16 * PAGE_NUM));  // 执行前5+地址指令
			}
		} else {
			tmp2 = (tmp - 0.8) / 0.2;
			if (tmp2 < 0.8) {
				ins[i] = ins[i - 1] + PHYSICAL_PAGE_SIZE + 16 * rand() % (PHYSICAL_PAGE_SIZE / 16 * 2);  // 执行后12地址指令
			} else if (tmp2 < 0.95) {
				ins[i] = ins[i - 1] + PHYSICAL_PAGE_SIZE * 3 + 16 * (rand() % (PHYSICAL_PAGE_SIZE / 16 * 2));  // 执行后34地址指令
			} else {
				ins[i] = ins[i - 1] + PHYSICAL_PAGE_SIZE * 5 + 16 * (rand() % (PHYSICAL_PAGE_SIZE / 16 * PAGE_NUM));  // 执行后5+地址指令
			}
		}
		if (ins[i] < 0) {
			ins[i] += PHYSICAL_PAGE_SIZE * MAX_PAGE_NUM - 16;
		} else if (ins[i] > PHYSICAL_PAGE_SIZE* MAX_PAGE_NUM - 16) {
			ins[i] -= PHYSICAL_PAGE_SIZE * MAX_PAGE_NUM - 16;
		}

		// 将指令序列变换成页地址流
		page[i] = ins[i] / PHYSICAL_PAGE_SIZE;
		tmp_sum += tmp;
		//printf("%lf\t%lf\t%d\t%d\n", tmp, tmp2, ins[i], page[i]);
	}

	//printf("%lf\n", tmp_sum / INS_NUM);
	printf("Frame \t OPT\tFIFO\tLRU\tLFU \n");
	//用户内存工作区从2个页面到28个页面
	for (int i = 2; i < PAGE_NUM; ++i) {
		printf("%d\t", i);
		printf("%6.3lf\t", OPT(i));
		printf("%6.3lf\t", FIFO(i));
		printf("%6.3lf\t", LRU(i));
		printf("%6.3lf\n", LFU(i));
	}
	return 0;
}
