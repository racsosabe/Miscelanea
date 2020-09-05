#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const int K = 100000 + 5;
const int MOD = 1000000000 + 7;

int add(int a, int b){
	return (a + b) % MOD;
}

int n;
int k;
int a[N];
bool vis[N][K];
int memo[N][K];

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	memo[0][0] = 1;
	memo[0][1] = -1;
	for(int i = 0; i <= n; i++){
		for(int j = 1; j <= k; j++){
			memo[i][j] = add(memo[i][j], memo[i][j - 1]);
		}
		if(i == n) break;
		for(int j = 0; j <= k; j++){
			int l = j;
			int r = min(k + 1, j + a[i] + 1);
			memo[i + 1][l] = add(memo[i + 1][l], memo[i][j]);
			memo[i + 1][r] = add(memo[i + 1][r], MOD - memo[i][j]);
		}
	}
	printf("%d\n", memo[n][k]);
	return 0;
}

