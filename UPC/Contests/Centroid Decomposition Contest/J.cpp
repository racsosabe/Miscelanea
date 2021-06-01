#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;
const int MASK = 1 << 20;

int n;
int T;
int h[N];
int a[N];
int L[N];
char s[N];
int in[N];
int out[N];
int Q[MASK];
int subtree[N];
bool removed[N];
long long ans[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		h[v] = h[u] ^ L[v];
		DFS(v, u);
		subtree[u] += subtree[v];
	}
	out[u] = T - 1;
}

int centroid(int u, int p, int sz){
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		if(2 * subtree[v] > sz) return centroid(v, u, sz);
	}
	return u;
}

void clear(int l, int r, int x){
	for(int i = l; i <= r; i++){
		int at = a[i];
		Q[h[at] ^ x] = 0;
	}
}

long long solve(int u, int p = -1){
	long long here = 0;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		here += solve(v, u);
	}
	here += Q[h[u]];
	for(int i = 0; i < 20; i++){
		here += Q[h[u] ^ (1 << i)];
	}
	ans[u] += here;
	return here;	
}

long long addRange(int u, int l, int r){
	int i = l;
	int dif = l <= r ? 1 : -1;
	long long res = 0LL;
	for(int i = l; i * dif <= r * dif; i += dif){
		int v = G[u][i];
		if(removed[v]) continue;
		res += solve(v, u);
		for(int j = in[v]; j <= out[v]; j++){
			int at = a[j];
			Q[h[at] ^ h[u]] += 1;
		}
	}
	clear(in[u], out[u], h[u]);
	return res;
}

void add(int u){
	T = 0;
	h[u] = L[u];
	DFS(u);
	long long here = 0;
	here += addRange(u, 0, G[u].size() - 1);
	here += addRange(u, G[u].size() - 1, 0);
	ans[u] += here / 2;
	Q[0] = 1;
	for(int v : G[u]){
		if(removed[v]) continue;
		ans[u] += solve(v, u);
	}
	Q[0] = 0;
	ans[u] += 1;
}

void decompose(int u){
	T = 0;
	DFS(u);
	int c = centroid(u, u, subtree[u]);
	add(c);
	removed[c] = true;
	for(int v : G[c]){
		if(removed[v]) continue;
		decompose(v);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++){
		L[i] = 1 << (s[i] - 'a');
	}
	decompose(1);
	for(int i = 1; i <= n; i++){
		printf("%lld%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
