#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;
const int MASK = 1 << 22;

int n;
int T;
int a[N];
int b[N];
int h[N];
int in[N];
int out[N];
int ans[N];
int nxt[N];
int last[MASK];
int subtree[N];
int values[N];
vector<int> G[N];
vector<int> libres;

void DFS(int u){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		h[v] = h[u] + 1;
		b[v] ^= b[u];
		DFS(v);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][i], G[u][0]);
		}
	}
	out[u] = T - 1;
}

int getMax(int mask){
	return last[mask] == -1 ? -n : values[last[mask]];
}

void insert(int mask, int height){
	int new_height = last[mask] != -1 ? max(values[last[mask]], height) : height;
	int pos = libres.back();
	libres.pop_back();
	nxt[pos] = last[mask];
	values[pos] = new_height;
	last[mask] = pos;
}

void remove(int mask){
	assert(last[mask] != -1);
	libres.emplace_back(last[mask]);
	last[mask] = nxt[last[mask]];
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	int cur = 0;
	insert(b[u], h[u]);
	for(int v : G[u]){
		cur = max(cur, ans[v]);
		if(v == G[u][0]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			int my_h = b[at];
			cur = max(cur, h[at] + getMax(my_h) - 2 * h[u]);
			for(int j = 0; j < 22; j++){
				int want = my_h ^ (1 << j);
				cur = max(cur, h[at] + getMax(want) - 2 * h[u]);
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			insert(b[at], h[at]);
		}
	}
	cur = max(cur, getMax(b[u]) - h[u]);
	for(int j = 0; j < 22; j++){
		int want = b[u] ^ (1 << j);
		cur = max(cur, getMax(want) - h[u]);
	}
	ans[u] = cur;
	if(!keep){
		for(int i = in[u]; i <= out[u]; i++){
			int at = a[i];
			remove(b[at]);
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		int p;
		scanf("%d", &p);
		char l = getchar();
		while(!isalpha(l)) l = getchar();
		b[i] = 1 << (l - 'a');
		G[p].emplace_back(i);
	}
	DFS(1);
	memset(last, -1, sizeof last);
	for(int i = 0; i < n; i++) libres.emplace_back(i);
	solve(1, 1);
	for(int i = 1; i <= n; i++){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}

