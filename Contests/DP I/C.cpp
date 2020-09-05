#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
bool vis[N];
int memo[N];
vector<int> G[N];

int DP(int u){
	if(vis[u]) return memo[u];
	int ans = 0;
	for(int v : G[u]){
		ans = max(ans, 1 + DP(v));
	}
	vis[u] = true;
	return memo[u] = ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++){
		ans = max(ans, DP(i));
	}
	printf("%d\n", ans);
	return 0;
}
