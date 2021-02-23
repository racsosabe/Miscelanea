#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int q;
int T;
int len;
int a[N];
int in[N];
int ft[N];
int out[N];
int ans[N];
long long l[N];
long long h[N];
int subtree[N];
bool removed[N];
long long val[N];
vector<int> G[N];
vector<int> W[N];
map<long long, int> id;
vector<int> queries[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	a[T] = u;
	in[u] = T++;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int w = W[u][i];
		if(v == p or removed[v]) continue;
		h[v] = h[u] + w;
		DFS(v, u);
		subtree[u] += subtree[v];
	}
	out[u] = T - 1;
}

int find(int u, int p, int root){
	for(int v : G[u]){
		if(v == p or removed[v]) continue;
		if(2 * subtree[v] > subtree[root]){
			return find(v, u, root);
		}
	}
	return u;
}

void compress(int u){
	set<long long> S;
	S.emplace(0);
	for(int v : G[u]){
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			S.emplace(h[at]);
		}
	}
	len = 0;
	for(auto x : S){
		val[len] = x;
		id[x] = len++;
	}
}

void update(long long x, int val){
	int pos = id[x];
	pos += 1;
	while(pos <= len){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int pos){
	pos += 1;
	int res = 0;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

int query(long long x){
	int lo = 0, hi = len - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(val[mi] <= x) lo = mi;
		else hi = mi - 1;
	}
	return getSum(lo);
}

void addQueries(int u){
	for(auto x : queries[u]){
		if(l[x] >= h[u]){
			ans[x] += query(l[x] - h[u]);
		}
	}
}

void solve(int u){
	T = 0;
	h[u] = 0;
	DFS(u);
	compress(u);
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			addQueries(at);
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			update(h[at], 1);
		}
	}
	for(int i = 0; i <= len; i++) ft[i] = 0;
	update(0, 1);
	for(int i = G[u].size() - 1; i >= 0; i--){
		int v = G[u][i];
		if(removed[v]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			addQueries(at);
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			update(h[at], 1);
		}
	}
	addQueries(u);
	for(int i = 0; i <= len; i++) ft[i] = 0;
}

void decompose(int root){
	T = 0;
	DFS(root);
	int c = find(root, root, root);
	solve(c);
	removed[c] = true;
	for(int v : G[c]){
		if(removed[v]) continue;
		decompose(v);
	}
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i < n; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		W[u].emplace_back(w);
		W[v].emplace_back(w);
	}
	for(int i = 1; i <= q; i++){
		int u;
		scanf("%d %lld", &u, &l[i]);
		queries[u].emplace_back(i);
	}
	decompose(1);
	for(int i = 1; i <= q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
