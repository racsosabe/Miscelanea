#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int LOG = 20;

int n;
int T;
int c[N];
int a[N];
int h[N];
int in[N];
int out[N];
int pot[LOG];
long long ans;
int ac[2][LOG];
int subtree[N];
bool removed[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		h[v] = h[u] ^ c[v];
		DFS(v, u);
		subtree[u] += subtree[v];
	}
	out[u] = T - 1;
}

int centroid(int u, int p, int root){
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		if(2 * subtree[v] > subtree[root]) return centroid(v, u, root);
	}
	return u;
}

void add(int u){
	T = 0;
	h[u] = c[u];
	DFS(u);
	memset(ac, 0, sizeof ac);
	for(int v : G[u]){
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			int val = h[at] ^ c[u];
			for(int j = 0; j < LOG; j++){
				int b = (val >> j) & 1;
				ans += 1LL * pot[j] * ac[b ^ 1][j];
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			ans += h[at];
			for(int j = 0; j < LOG; j++){
				int b = (h[at] >> j) & 1;
				ac[b][j] += 1;
			}
		}
	}
}

void decompose(int u){
	T = 0;
	DFS(u);
	int c = centroid(u, u, u);
	removed[c] = true;
	add(c);
	for(int v : G[c]){
		if(removed[v]) continue;
		decompose(v);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", c + i);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	pot[0] = 1;
	for(int i = 1; i < LOG; i++) pot[i] = pot[i - 1] << 1;
	ans = accumulate(c + 1, c + n + 1, 0LL);
	decompose(1);
	printf("%lld\n", ans);
	return 0;
}
