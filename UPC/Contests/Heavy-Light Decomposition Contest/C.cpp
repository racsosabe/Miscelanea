#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int k[N];
int c[N];
int Q[N];
int F[N];
int ans[N];
bool vis[N];
int subtree[N];
vector<int> G[N];
vector<int> queries[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p){
			swap(G[u][i], G[u].back());
		}
		int v = G[u][i];
		if(v == p) continue;
		DFS(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][i], G[u][0]);
		}
	}
	if(p != -1) G[u].pop_back();
}

void add(int u, int x, int start){
	if(x > 0){
		Q[++F[c[u]]] += 1;
	}
	else{
		Q[F[c[u]]--] -= 1;
	}
	for(int i = start; i < G[u].size(); i++){
		add(G[u][i], x, 0);
	}
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	add(u, 1, 1);
	for(int x : queries[u]) ans[x] = Q[k[x]];
	if(!keep) add(u, -1, 0);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", c + i);
		vis[c[i]] = true;
	}
	for(int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	for(int i = 1; i <= m; i++){
		int v;
		scanf("%d %d", &v, &k[i]);
		queries[v].emplace_back(i);
	}
	DFS(1);
	for(int i = 1; i < N; i++) if(vis[i]) Q[0] += 1;
	solve(1, 1);
	for(int i = 1; i <= m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
