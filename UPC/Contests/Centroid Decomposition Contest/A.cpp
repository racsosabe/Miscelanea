#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int gcd(int a, int b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}

int n;
int T;
int a[N];
int h[N];
int c[N];
int F[N];
int in[N];
int out[N];
int mobius[N];
int subtree[N];
long long Q[N];
bool removed[N];
long long ans[N];
vector<int> D[N];
vector<int> G[N];
bool composite[N];

void init(){
	for(int i = 1; i <= 200000; i++){
		for(int j = i; j <= 200000; j += i) D[j].emplace_back(i);
	}
	mobius[1] = 1;
	for(int i = 2; i <= 200000; i++){
		if(not composite[i]){
			mobius[i] = -1;
			for(int j = i << 1; j <= 200000; j += i){
				composite[j] = true;
				if((j / i) % i == 0){
					mobius[j] = 0;
				}
				else{
					mobius[j] = -mobius[j / i];
				}
			}
		}
	}
}

void DFS(int u, int p = -1){
	in[u] = T;
	a[T++] = u;
	subtree[u] = 1;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		h[v] = gcd(h[u], c[v]);
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
	for(int x : D[h[u]]) Q[x] += 1;
	for(int v : G[u]){
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			for(int x : D[h[at]]){
				Q[x] += F[x] + 1;
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			for(int x : D[h[at]]){
				F[x] += 1;
			}
		}
	}
	for(int i = in[u]; i <= out[u]; i++){
		int at = a[i];
		for(int x : D[h[at]]){
			F[x] = 0;
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

void solve(){
	for(int i = 1; i <= 200000; i++){
		long long cur = 0LL;
		for(int j = i; j <= 200000; j += i){
			cur += Q[j] * mobius[j / i];
		}
		ans[i] = cur;
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
	init();
	decompose(1);
	solve();
	for(int i = 1; i <= 200000; i++){
		if(ans[i] == 0) continue;
		printf("%d %lld\n", i, ans[i]);
	}
	return 0;
}
