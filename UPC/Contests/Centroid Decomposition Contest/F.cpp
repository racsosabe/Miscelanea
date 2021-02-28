#include<bits/stdc++.h>
using namespace::std;

const int N = 1000010;
const int LOG = 21;

int n;
int q;
int ans;
int h[N];
int v[N];
int nodes;
int par[N];
int out[N];
int subtree[N];
bool removed[N];
int dis[N][LOG];
vector<int> G[N];
pair<int, int> max1[N];
pair<int, int> max2[N];

void init(){
	n = 4;
	for(int i = 2; i <= n; i++){
		G[i].emplace_back(1);
		G[1].emplace_back(i);
	}
}

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		DFS(v, u);
		subtree[u] += subtree[v];
	}
}

int centroid(int u, int p, int sz){
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		if(2 * subtree[v] > sz) return centroid(v, u, sz);
	}
	return u;
}

void add(int u, int p, int lvl){
	dis[u][lvl] = h[u];
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		h[v] = h[u] + 1;
		add(v, u, lvl);
	}
}

void decompose(int u, int p = -1, int lvl = 0){
	DFS(u, p);
	int c = centroid(u, u, subtree[u]);
	h[c] = 0;
	par[c] = p;
	out[c] = lvl;
	add(c, c, lvl);
	removed[c] = true;
	int cnt = 0;
	vector<int> children;
	for(int v : G[c]){
		if(removed[v]) continue;
		decompose(v, c, lvl + 1);
	}
}

void update(int u){
	int p = out[u] - 1;
	int last = u;
	for(int v = par[u]; v != -1; v = par[v]){
		int d = dis[u][p];
		if(max1[v].second == last){
			max1[v].first = max(max1[v].first, d);
		}
		else if(max2[v].second == last){
			max2[v].first = max(max2[v].first, d);
		}
		else{
			if(max2[v].first < d){
				max2[v] = make_pair(d, last);
			}
		}
		if(max2[v].first > max1[v].first){
			swap(max1[v], max2[v]);
		}
		if(v <= nodes){
			ans = max(ans, max1[v].first + max2[v].first);
		}
		p -= 1;
		last = v;
	}
}

int main(){
	init();
	scanf("%d", &q);
	for(int i = 1; i <= q; i++){
		scanf("%d", &v[i]);
		int x = v[i];
		G[x].emplace_back(n + 1);
		G[x].emplace_back(n + 2);
		G[n + 1].emplace_back(x);
		G[n + 2].emplace_back(x);
		n += 2;
	}
	decompose(1);
	for(int i = 1; i <= n; i++){
		max1[i] = make_pair(0, 0);
		max2[i] = make_pair(-1, -1);
	}
	ans = 0;
	nodes = 1;
	for(int i = 2; i <= 4; i++){
		update(i);
		nodes += 1;
	}
	for(int i = 1; i <= q; i++){
		update(nodes + 1);
		nodes += 1;
		update(nodes + 1);
		nodes += 1;
		printf("%d\n", ans);
	}
	return 0;
}
