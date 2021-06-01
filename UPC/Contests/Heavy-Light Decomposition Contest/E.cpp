#include<bits/stdc++.h>
using namespace::std;

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

int mul(int a, int b, int m){
	return (1ll * a * b) % m;
}

int pow_mod(int a, int b, int m){
	int r = 1 % m;
	while(b > 0){
		if(b & 1) r = (1ll * r * a) % m;
		a = (1ll * a * a) % m;
		b >>= 1;
	}
	return r;
}

const int N = 100000 + 5;

int n;
int M;
int T;
int h[N];
int a[N];
int in[N];
int out[N];
int res[2][N];
long long ans;
int pot[2][N];
int subtree[N];
vector<int> G[N];
vector<int> W[N];
map<int, int> ac[2];

void init(){
	pot[0][0] = 1;
	for(int i = 1; i <= n; i++){
		pot[0][i] = (10ll * pot[0][i - 1]) % M;
	}
	pot[1][n] = pow_mod(pot[0][n], phi(M) - 1, M);
	for(int i = n - 1; i >= 0; i--){
		pot[1][i] = (10ll * pot[1][i + 1]) % M;
	}
}

void update(int u, int p, int w){
	h[u] = h[p] + 1;
	for(int i = 0; i < 2; i++){
		res[i][u] = (res[i][p] + (1ll * w * pot[i][h[p] + i]) % M) % M;
	}
}

void DFS(int u, int p = -1){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p){
			swap(G[u][i], G[u].back());
			swap(W[u][i], W[u].back());
		}
		int v = G[u][i];
		if(v == p) continue;
		int w = W[u][i];
		update(v, u, w);
		DFS(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][0], G[u][i]);
			swap(W[u][0], W[u][i]);
		}

	}
	if(p != -1){
		G[u].pop_back();
		W[u].pop_back();
	}
	out[u] = T - 1;
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	int extra = (mul(res[1][u], pot[0][h[u]], M) + mul(res[0][u], pot[1][h[u]], M)) % M;
	for(int v : G[u]){
		if(v == G[u][0]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			for(int j = 0; j < 2; j++){
				int p = pot[j ^ 1][h[u]];
				int ip = pot[j][h[u]];
				int want = mul(p, (extra + M - mul(p, res[j][at], M)) % M, M);
				ans += ac[j ^ 1][want];
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			for(int j = 0; j < 2; j++){
				ac[j][res[j][at]] += 1;
			}
		}
	}
	for(int i = 0; i < 2; i++){
		ans += ac[i][res[i][u]];
		ac[i][res[i][u]] += 1;
	}
	if(!keep){
		for(int i = in[u]; i <= out[u]; i++){
			int at = a[i];
			for(int j = 0; j < 2; j++){
				ac[j][res[j][at]] -= 1;
				if(ac[j][res[j][at]] == 0) ac[j].erase(res[j][at]);
			}
		}
	}
}

int main(){
	scanf("%d %d", &n, &M);
	init();
	for(int i = 1; i < n; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		W[u].emplace_back(w);
		W[v].emplace_back(w);
	}
	DFS(0);
	solve(0, 1);
	printf("%lld\n", ans);
	return 0;
}
