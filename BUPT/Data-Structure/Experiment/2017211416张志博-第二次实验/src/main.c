//从开始位置（start）找出到出口（end）的通路，并从start到end输出；输出路径的长度。
//采用下图迷宫
//可以将节点进行编号，从1开始编号，编号次序从上到下，从左到右；保存每条边，根据两个节点之间是否有边，来决定是否能够走通；
//将边保存在文件中，用俩个端点来表示一条边；
//每个节点的分支数不一样，要求根据分支数决定遍历的方向数，不能用恒定的遍历方向数。
//需要提交设计报告和源代码，要求和《实验一》一样
//补充：找到从start到end的一条最短的路径；当迷宫有多个出口应该如何找到最近的出口；


#include "maze.h"

int main(void) {
	ALGraph G;
	int start = 1, end[MVNum], endNum = 1;

	freopen("maze.txt", "r", stdin);
	if (!createUDG(&G))
		return 1;
	freopen("CON", "r", stdin);

	printf("\nStart:(0 to exit)");
	scanf("%d", &start);
	printf("\nNumber of ends:");
	scanf("%d", &endNum);
	printf("\nEnds:");
	for (int i = 0; i < endNum; ++i)
		scanf("%d", &end[i]);
	while (start > 0 && (start <= G.vexnum) && endNum > 0 && (endNum < G.vexnum)) {
		if (!printShortestPath(G, start, end, endNum))
			return 2;
		printf("\nStart:(0 to exit)");
		scanf("%d", &start);
		printf("\nNumber of ends:");
		scanf("%d", &endNum);
		printf("\nEnds:");
		for (int i = 0; i < endNum; ++i)
			scanf("%d", &end[i]);
	}


	system("pause");

	return 0;
}