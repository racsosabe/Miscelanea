#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int b[N];
int h[N];
int ans[N];
int suma[N];
int subtree[N];
vector<int> G[N];
set< pair<int, int> > S;

void DFS(int u){
	subtree[u] = 1;
	suma[h[u]] += b[u];
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		h[v] = h[u] + 1;
		DFS(v);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]) swap(G[u][i], G[u][0]);
	}
}

void add(int u, int x, int start){
	if(x > 0){
		S.erase(make_pair(suma[h[u]], h[u]));
		suma[h[u]] -= b[u];
		S.emplace(make_pair(suma[h[u]], h[u]));
	}
	else{
		S.erase(make_pair(suma[h[u]], h[u]));
		suma[h[u]] += b[u];
		S.emplace(make_pair(suma[h[u]], h[u]));
	}
	for(int i = start; i < G[u].size(); i++){
		add(G[u][i], x, 0);
	}
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	add(u, 1, 1);
	ans[u] = (*S.rbegin()).first;
	if(!keep) add(u, -1, 0);
}

void clearAll(){
	S.clear();
	for(int i = 0; i <= n; i++){
		G[i].clear();
		suma[i] = 0;
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for(int i = 2; i <= n; i++){
			int x;
			scanf("%d", &x);
			G[x].emplace_back(i);
		}
		DFS(1);
		for(int i = 0; i < n; i++){
			S.emplace(make_pair(suma[i], i));
		}
		solve(1, 1);
		for(int i = 2; i <= n; i++){
			printf("%d\n", ans[i]);
		}
		if(t) clearAll();
	}
	return 0;
}
