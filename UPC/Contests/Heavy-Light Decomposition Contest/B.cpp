#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int h[N];
int ans[N];
int st[4 * N];
int subtree[N];
vector<int> G[N];

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
	if(p != -1) G[u].pop_back();
}

void update(int x, int y, int pos = 1, int l = 0, int r = n){
	if(l == r){
		st[pos] += y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = max(st[2 * pos], st[2 * pos + 1]);
}

int getMaxPos(int pos = 1, int l = 0, int r = n){
	if(l == r) return l;
	int mi = (l + r) / 2;
	if(st[2 * pos] >= st[2 * pos + 1]) return getMaxPos(2 * pos, l, mi);
	else return getMaxPos(2 * pos + 1, mi + 1, r);
}

void add(int u, int x, int start){
	update(h[u], x);
	for(int i = start; i < G[u].size(); i++){
		add(G[u][i], x, 0);
	}
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	add(u, 1, 1);
	ans[u] = getMaxPos(1) - h[u];
	if(!keep) add(u, -1, 0);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(1);
	solve(1, 1);
	for(int i = 1; i <= n; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
