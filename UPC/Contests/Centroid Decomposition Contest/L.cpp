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
			pf[i] = i;
			primos.emplace_back(i);
		}
		for(int p : primos){
			if(i * p >= N) break;
			composite[i * p] = true;
			pf[i * p] = p;
			if(i % p == 0) break;
		}
	}
	for(int i = 2; i < N; i++){
		int x = i;
		while(x != 1){
			int f = pf[x];
			int e = 0;
			while(x % f == 0){
				e += 1;
				x /= f;
			}
			if(e > 1){
				cnt[i] = 3;
				break;
			}
			else{
				cnt[i] += 1;
			}
		}
	}
}

bool checkProd(long long x, long long y){
	if(x == 1 or y == 1) return true;
	return x % y != 0;
}

void update(int u, int p, int w){
	if(w == 1){
		h[u] = h[p];
		c[u] = c[p];
	}
	else{
		if(cnt[w] + c[p] > 2){
			h[u] = -1;
			c[u] = 3;
		}
		else{
			if(checkProd(h[p], w)){
				h[u] = h[p] * w;
				c[u] = c[p] + cnt[w];
			}
			else{
				h[u] = -1;
				c[u] = 3;
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
		update(v, u, w);
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
	vector<int> Q(3, 0);
	Q[0] = 1;
	for(int v : G[u]){
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			if(c[at] <= 2){
				ans += Q[2 - c[at]];
				if(c[at] == 1) ans -= F[h[at]];
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			if(c[at] <= 2){
				Q[c[at]] += 1;
				if(c[at] == 1) F[h[at]] += 1;
			}
		}
	}
	for(int i = in[u]; i <= out[u]; i++){
		int at = a[i];
		if(c[at] == 1) F[h[at]] = 0;
	}
}

void decompose(int u){
	T = 0;
	h[u] = 1;
	c[u] = 0;
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
