#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input = true, bool output = true){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 100000 + 5;

int n;
int L;
int R;
int T;
int len;
int a[N];
int h[N];
int ft[N];
int in[N];
int out[N];
int cnt[N];
long long ans;
int subtree[N];
bool removed[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		h[v] = h[u] + 1;
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

int query(int l, int r){
	if(r < 0) return 0;
	l = max(l, 0);
	return cnt[r] - (l > 0 ? cnt[l - 1] : 0);
}

long long compute(int l, int r){
	int max_h = 0;
	for(int i = l; i <= r; i++){
		int at = a[i];
		max_h = max(max_h, h[at]);
		cnt[h[at]] += 1;
	}
	long long res = 0;
	for(int i = 1; i <= max_h; i++){
		cnt[i] += cnt[i - 1];
	}
	int ac = 0;
	for(int i = 0; i <= max_h; i++){
		int A = L - i;
		int B = R - i;
		if(i < A){
			ac = cnt[i];
			continue;
		}
		B = min(B, i - 1);
		int here = cnt[i] - ac;
		res += 1LL * query(A, B) * here;
		if(L <= 2 * i and 2 * i <= R) res += 1LL * here * (here - 1) / 2;
		ac = cnt[i];
	}
	for(int i = 0; i <= max_h; i++){
		cnt[i] = 0;
	}
	return res;
}

void add(int u){
	T = 0;
	h[u] = 0;
	DFS(u);
	ans += compute(in[u], out[u]);
	for(int v : G[u]){
		if(removed[v]) continue;
		ans -= compute(in[v], out[v]);
	}
}

void decompose(int u){
	T = 0;
	DFS(u, u);
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
		removed[i] = false;
	}
	ans = 0;
}

int main(){
	setIO("awesome", 1, 0);
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &n, &L, &R);
		L = n - L - 1;
		R = n - R - 1;
		swap(L, R);
		for(int i = 1; i < n; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		decompose(1);
		printf("%lld\n", ans);
		if(t) clearAll();
	}
	return 0;
}
