#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int h[2][N];
long long memo[2][N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < 2; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &h[i][j]);
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 2; j++){
			memo[j][i] = max(memo[j][i-1], memo[j^1][i-1] + h[j][i]);
		}
	}
	printf("%lld\n", max(memo[0][n], memo[1][n]));
	return 0;
}
