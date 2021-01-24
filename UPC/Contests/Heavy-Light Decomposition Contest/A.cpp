#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

int n;
int m;
int h[N];
char s[N];
int he[N];
bool ans[N];
int mask[N];
int subtree[N];
vector<int> G[N];
vector<int> Q[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p){
			swap(G[u][i], G[u].back());
		}
		int v = G[u][i];
		if(v == p) continue;
		h[v] = h[u] + 1;
		DFS(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][i], G[u][0]);
		}
	}
}

void add(int u, int x, int start){
	mask[h[u]] ^= 1 << (s[u] - 'a');
	for(int i = start; i < G[u].size(); i++){
		add(G[u][i], x, 0);
	}
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	add(u, 1, 1);
	for(int x : Q[u]){
		ans[x] = __builtin_popcount(mask[he[x]]) <= 1;
	}
	if(!keep) add(u, -1, 0);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 2; i <= n; i++){
		int p;
		scanf("%d", &p);
		G[p].emplace_back(i);
	}
	scanf("%s", s + 1);
	for(int i = 1; i <= m; i++){
		int v;
		scanf("%d %d", &v, &he[i]);
		Q[v].emplace_back(i);
	}
	h[1] = 1;
	DFS(1);
	solve(1, 1);
	for(int i = 1; i <= m; i++) puts(ans[i] ? "Yes" : "No");
	return 0;
}
