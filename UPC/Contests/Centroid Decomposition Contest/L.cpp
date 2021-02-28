#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 100000 + 5;

int n;
int T;
int a[N];
int c[N];
int F[N];
int pf[N];
int in[N];
int out[N];
int cnt[N];
long long ans;
long long h[N];
int subtree[N];
bool removed[N];
vector<int> G[N];
vector<int> W[N];
bool composite[N];
vector<int> primos;

void init(){
	for(int i = 2; i < N; i++){
		if(not composite[i]){
			cnt[i] = 1;
			primos.emplace_back(i);
		}
		for(int p : primos){
			if(i * p >= N) break;
			composite[i * p] = true;
			if(i % p == 0){
				cnt[i * p] = 3;
			}
			else{
				cnt[i * p] = cnt[i] + 1;
			}
		}
	}
}

void DFS(int u, int p = -1){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int w = W[u][i];
		if(removed[v] or v == p) continue;
		if(h[u] == -1) c[v] = 3;
		else if(h[u] % w == 0 and w > 1){
			c[v] = 3;
		}
		else if(h[u] != -1){
			h[v] = h[u] * w;
			c[v] = c[u] + cnt[w];
		}
		c[v] = min(c[v], 3);
		if(c[v] > 2) h[v] = -1;
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

void add(int u){
	T = 0;
	h[u] = 1;
	c[u] = 0;
	DFS(u);
	int cnt0 = 1;
	int cnt1 = 0;
	for(int v : G[u]){
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			if(c[at] == 2){
				ans += cnt0;
			}
			if(c[at] == 1){
				ans += cnt1 - F[h[at]];
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			if(c[at] == 1){
				F[h[at]] += 1;
				cnt1 += 1;
			}
			if(h[at] == 1) cnt0 += 1;
		}
	}
	for(int i = in[u]; i <= out[u]; i++){
		int at = a[i];
		if(c[at] == 1) F[h[at]] = 0;
	}
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

void clearAll(){
	for(int i = 1; i <= n; i++){
		G[i].clear();
		W[i].clear();
		removed[i] = false;
	}
}

int main(){
	setIO("evaluations", 1, 0);
	init();
	int t;
	scanf("%d", &t);
	for(int caso = 1; caso <= t; caso++){
		scanf("%d", &n);
		for(int i = 1; i < n; i++){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
			W[u].emplace_back(w);
			W[v].emplace_back(w);
		}
		ans = 0;
		decompose(1);
		printf("Case %d: %lld\n", caso, ans);
		if(caso < t) clearAll();
	}
	return 0;
}
