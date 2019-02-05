//�ӿ�ʼλ�ã�start���ҳ������ڣ�end����ͨ·������start��end��������·���ĳ��ȡ�
//������ͼ�Թ�
//���Խ��ڵ���б�ţ���1��ʼ��ţ���Ŵ�����ϵ��£������ң�����ÿ���ߣ����������ڵ�֮���Ƿ��бߣ��������Ƿ��ܹ���ͨ��
//���߱������ļ��У��������˵�����ʾһ���ߣ�
//ÿ���ڵ�ķ�֧����һ����Ҫ����ݷ�֧�����������ķ������������ú㶨�ı�����������
//��Ҫ�ύ��Ʊ����Դ���룬Ҫ��͡�ʵ��һ��һ��
//���䣺�ҵ���start��end��һ����̵�·�������Թ��ж������Ӧ������ҵ�����ĳ��ڣ�


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