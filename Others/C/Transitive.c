#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
//#define DEBUG

int isTransitive(int(*a)[N]);
void generateMartix(int(*a)[N], int k);

int main() {
	int cnt = 0;
	int a[N][N];
	int total = (int)pow(2.0, (double)N*N);

	for (int i = 0; i < total; ++i) {
		generateMartix(a, i);
		if (isTransitive(a))
			cnt++;
#ifdef DEBUG
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%d", a[i][j]);
			printf("\n");
		}
		printf("\n%d\n", cnt);
		system("pause");
#endif // DEBUG
	}
	printf("%d\n", cnt);
	system("pause");

	return 0;
}

int isTransitive(int(*a)[N]) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (a[i][j])
				for (int k = 0; k < N; ++k)
					if (a[j][k] && !a[i][k])
						return 0;
	return 1;
}

void generateMartix(int(*a)[N], int k) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; j++) {
			a[i][j] = k & 1;
			k >>= 1;
		}
}