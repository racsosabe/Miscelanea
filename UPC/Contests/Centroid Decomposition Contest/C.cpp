#include<bits/stdc++.h>
using namespace::std;

int mul(int a, int b, int m){
	return (1LL * a * b) % m;
}

int pow_mod(int a, int b, int m){
	int r = 1 % m;
	while(b > 0){
		if(b & 1) r = mul(r, a, m);
		a = mul(a, a, m);
		b >>= 1;
	}
	return r;
}

int phi(int x){
	int ans = x;
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0){
			while(x % i == 0) x /= i;
			ans -= ans / i;
		}
	}
	if(x > 1) ans -= ans / x;
	return ans;
}

const int N = 100000 + 5;

int n;
int M;
int T;
int a[N];
int h[N];
int in[N];
int out[N];
int val[2][N];
long long ans;
int pot[2][N];
int subtree[N];
bool removed[N];
vector<int> G[N];
vector<int> W[N];
map<int, int> F[2];

void init(){
	pot[0][0] = 1;
	for(int i = 1; i <= n; i++) pot[0][i] = mul(pot[0][i - 1], 10, M);
	pot[1][n] = pow_mod(pot[0][n], phi(M) - 1, M);
	for(int i = n - 1; i >= 0; i--){
		pot[1][i] = mul(pot[1][i + 1], 10, M);
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
		h[v] = h[u] + 1;
		val[0][v] = (val[0][u] + mul(pot[0][h[u]], w, M)) % M;
		val[1][v] = (val[1][u] + mul(pot[1][h[v]], w, M)) % M;
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
	h[u] = 0;
	val[0][u] = val[1][u] = 0;
	DFS(u);
	for(int v : G[u]){
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			for(int b = 0; b < 2; b++){
				int left = (M - val[b][at]) % M;
				if(F[b ^ 1].count(left)){
					ans += F[b ^ 1][left];
				}
				if(left == 0) ans += 1;
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			for(int b = 0; b < 2; b++){
				F[b][val[b][at]] += 1;
			}
		}
	}
	for(int i = 0; i < 2; i++) F[i].clear();
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
	scanf("%d %d", &n, &M);
	for(int i = 1; i < n; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		W[u].emplace_back(w);
		W[v].emplace_back(w);
	}
	init();
	decompose(0);
	printf("%lld\n", ans);
	return 0;
}
