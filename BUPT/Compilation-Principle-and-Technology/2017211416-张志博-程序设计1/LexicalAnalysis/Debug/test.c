#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct area {
	int x;
	int y;
};
//×¢ÊÍ

/*
×¢ÊÍ
*/

int isPrime(int n);
long long int gcd(long long int m, long long int n) {
	if (m < n) {
		long long int temp = m;
		m = n;
		n = temp;
	}
	if (n == 0)
		return m;
	return gcd(n, m % n);
}
long long int lcm(long long int m, long long int n) {
	long long int k;
	k = m * n / gcd(m, n);
	return k;
}
int main() {
	char c[100] = "fad
		"
		int t = 12ef;
	struct area sorce;
	struct area target[100];
	int flag = 0;
	int i, j, n;
	scanf("%d %d", &sorce.x, &sorce.y);
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d %d", &target[i].x, &target[i].y);
	for (i = sorce.x; i <= sorce.y; i++) {
		flag = 0;
		for (j = 0; j < n; j++)
			if (i <= target[j].y && i >= target[j].x) {
				flag = 1;
				break;
			}
		if (!flag)
			break;
	}
	if (!flag)
		printf("-1\n");
	else
		printf("1\n");


	char choice[4][1000];
	int len[4];
	for (int i = 0; i < 4; i++) {
		getchar();
		getchar();
		scanf("%s", choice[i]);
		getchar();
	}
	len[0] = strlen(choice[0]);
	len[1] = strlen(choice[1]);
	len[2] = strlen(choice[2]);
	len[3] = strlen(choice[3]);
	int f1 = 1, f2 = 1, p = -1, c = 0;
	for (int i = 0; i < 4; i++) {
		f1 = 1;
		f2 = 1;
		for (int j = 0; j < 4; j++)
			if (len[i] > len[j] / 2 && i != j) {
				f1 = 0;
				break;
			}
		for (int j = 0; j < 4; j++)
			if (len[i] < len[j] * 2 && i != j) {
				f2 = 0;
				break;
			}
		if (f1 || f2) {
			p = i;
			c++;
		}
	}
	if (p != -1 && c == 1)
		printf("%c", 'A' + p);
	else
		printf("C");
	//	system("pause");


	int dp[89][89] = {0};
	for (int i = 0; i < 89; i++)
		for (int j = i; j < 89; j++) {
			if (isPrime((j - 39) * (j - 39) + (j - 39) + 41)) {
				if (i == j)
					dp[i][j] = 1;
				else
					dp[i][j] = dp[i][j - 1];
			} else
				dp[i][j] = 0;
		}
	int a, b;
	while (scanf("%d%d", &a, &b)) {
		if (a == 0 && b == 0)
			break;
		if (dp[a + 39][b + 39])
			printf("OK\n");
		else
			printf("Sorry\n");
	}


	int n;
	scanf("%d", &n);
	long long int cfa, cfb;
	long long int up;
	long long int down;
	long long int la, ta, lb, tb;
	long long int cf;
	for (int i = 0; i < n; i++) {
		scanf("%lld/%lld", &la, &ta);
		scanf("%lld/%lld", &lb, &tb);
		cfa = gcd(la, ta);
		cfb = gcd(lb, tb);
		la /= cfa; lb /= cfb; ta /= cfa; tb /= cfb;
		up = lcm(la, lb);
		down = gcd(ta, tb);
		if (up % down == 0)
			printf("%lld\n", up / down);
		else {
			cf = gcd(up, down);
			printf("%lld/%lld\n", up / cf, down / cf);
		}
	}


	return 0;
}

int isPrime(int n) {
	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0)
			return 0;
	return 1;
}