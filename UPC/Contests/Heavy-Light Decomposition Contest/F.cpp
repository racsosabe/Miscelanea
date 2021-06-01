#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int inf = 1e9;

int n;
int m;
int T;
int h[N];
int d[N];
int a[N];
int b[N];
int in[N];
int out[N];
int nxt[N];
int par[N];
int subtree[N];
vector<int> G[N];
int st[2][4 * N];
int lazy[2][4 * N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p) swap(G[u][i], G[u].back());
		int v = G[u][i];
		if(v == p) continue;
		DFS(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]) swap(G[u][0], G[u][i]);
	}
	if(p != -1) G[u].pop_back();
}

void HLD(int u){
	in[u] = T++;
	for(int v : G[u]){
		h[v] = h[u] + 1;
		par[v] = u;
		nxt[v] = v == G[u][0] ? nxt[u] : v;
		HLD(v);
	}
	out[u] = T - 1;
}

int getDis(int u, int v){
	int res = 0;
	while(nxt[u] != nxt[v]){
		if(h[nxt[u]] < h[nxt[v]]) swap(u, v);
		res += in[u] - in[nxt[u]] + 1;
		u = par[nxt[u]];
	}
	if(h[u] > h[v]) swap(u, v);
	res += in[v] - in[u] + 1;
	return res;
}

void push(int id, int pos, int l, int r){
	if(lazy[id][pos]){
		st[id][pos] = lazy[id][pos];
		if(l < r){
			lazy[id][2 * pos] = lazy[id][pos];
			lazy[id][2 * pos + 1] = lazy[id][pos];
		}
		lazy[id][pos] = 0;
	}
}

void update(int id, int x, int y, int z, int pos = 1, int l = 0, int r = n - 1){
	push(id, pos, l, r);
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y){
		lazy[id][pos] = z;
		push(id, pos, l, r);
		return;
	}
	int mi = (l + r) / 2;
	update(id, x, y, z, 2 * pos, l, mi);
	update(id, x, y, z, 2 * pos + 1, mi + 1, r);
	if(id == 0) st[id][pos] = min(st[id][2 * pos], st[id][2 * pos + 1]);
	else st[id][pos] = max(st[id][2 * pos], st[id][2 * pos + 1]);
}

int query(int id, int x, int y, int pos = 1, int l = 0, int r = n - 1){
	push(id, pos, l, r);
	if(y < l or r < x or x > y) return id == 0 ? inf : -inf;
	if(x <= l and r <= y) return st[id][pos];
	int mi = (l + r) / 2;
	if(id == 0) return min(query(id, x, y, 2 * pos, l, mi), query(id, x, y, 2 * pos + 1, mi + 1, r));
	else return max(query(id, x, y, 2 * pos, l, mi), query(id, x, y, 2 * pos + 1, mi + 1, r));
}

bool valid(int u, int v){
	int cur_min = inf;
	int cur_max = -inf;
	while(nxt[u] != nxt[v]){
		if(h[nxt[u]] < h[nxt[v]]) swap(u, v);
		int l = in[nxt[u]], r = in[u];
		cur_min = min(cur_min, query(0, l, r));
		cur_max = max(cur_max, query(1, l, r));
		u = par[nxt[u]];
	}
	if(h[u] > h[v]) swap(u, v);
	int l = in[u], r = in[v];
	cur_min = min(cur_min, query(0, l, r));
	cur_max = max(cur_max, query(1, l, r));
	return cur_min == cur_max;
}

void modify(int u, int v, int x){
	while(nxt[u] != nxt[v]){
		if(h[nxt[u]] < h[nxt[v]]) swap(u, v);
		update(0, in[nxt[u]], in[u], x);
		update(1, in[nxt[u]], in[u], x);
		u = par[nxt[u]];
	}
	if(h[u] > h[v]) swap(u, v);
	update(0, in[u], in[v], x);
	update(1, in[u], in[v], x);
}

bool solve(){
	vector<int> p(m);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return d[i] > d[j];
	});
	int pos = 1;
	for(int i : p){
		if(!valid(a[i], b[i])) return false;
		modify(a[i], b[i], pos++);
	}
	return true;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(1);
	HLD(1);
	for(int i = 1; i <= m; i++){
		scanf("%d %d", a + i, b + i);
		d[i] = getDis(a[i], b[i]);
	}
	puts(solve() ? "Yes" : "No");
	return 0;
}
