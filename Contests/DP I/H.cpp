#include<bits/stdc++.h>
using namespace::std;

const int N = 22;
const int MASK = 1<<21;
const int MOD = 1000000000 + 7;

int add(int a, int b){
	return (a + b) % MOD;
}

int n;
int a[N][N];
bool vis[MASK];
int memo[MASK];

int DP(int mask){
	int man = n - __builtin_popcount(mask);
	if(mask == 0) return 1;
	if(vis[mask]) return memo[mask];
	int ans = 0;
	for(int nxt = mask; nxt > 0; nxt &= nxt - 1){
		int woman = 31 - __builtin_clz(nxt & (-nxt));
		if(a[man][woman]){
			ans = add(ans, DP(mask ^ (1 << woman)));
		}
	}
	vis[mask] = true;
	return memo[mask] = ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	printf("%d\n", DP((1 << n) - 1));
	return 0;
}

