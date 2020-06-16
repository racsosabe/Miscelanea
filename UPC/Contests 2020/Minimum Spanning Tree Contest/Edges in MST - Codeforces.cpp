#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int T = 0;
int n, m;
int a[N];
int b[N];
int w[N];
int p[N];
int up[N];
int low[N];
int ans[N];
int par[N];
int vis[N];
int sizes[N];
bool cant[N];
int descubre[N];
vector<int> G[N];
vector<int> E[N];

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
}

void addEdge(int u, int v, int e){
	G[u].emplace_back(v);
	G[v].emplace_back(u);
	E[u].emplace_back(e);
	E[v].emplace_back(e);
}

void DFS(int u, int p = -1){
	T += 1;
	descubre[u] = T;
	low[u] = descubre[u];
	vis[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int e = E[u][i];
		if(v == p) continue;
		if(vis[v] == 1){
			low[u] = min(low[u], descubre[v]);
		}
		else{
			if(vis[v] == 0){
				DFS(v, u);
				low[u] = min(low[u], low[v]);
			}
			if(low[v] > descubre[u] and !cant[e]){
				ans[e] = 2;
			}
		}
	}
	vis[u] = 2;
	T += 1;
}

void getGraph(int L, int R, vector<int> &nodes, vector<int> &edg){
	vector< pair< pair<int,int>, int > > edges;
	for(int i = L; i < R; i++){
		if(get(a[p[i]]) == get(b[p[i]])) continue;
		edg.emplace_back(p[i]);
		ans[p[i]] = 1;
		int u = get(a[p[i]]);
		int v = get(b[p[i]]);
		if(u > v) swap(u, v);
		edges.emplace_back(make_pair(make_pair(u, v), p[i]));
	}
	sort(edges.begin(), edges.end());
	int l = 0, r = 0;
	while(l < edges.size()){
		while(r < edges.size() and edges[l].first == edges[r].first){
			addEdge(edges[r].first.first, edges[r].first.second, edges[r].second);
			nodes.emplace_back(edges[r].first.first);
			nodes.emplace_back(edges[r].first.second);
			r += 1;
		}
		if(r - l > 1){
			for(int i = l; i < r; i++){
				cant[edges[i].second] = true;
			}
		}
		l = r;
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++){
		scanf("%d %d %d", &a[i], &b[i], &w[i]);
		p[i] = i;
	}
	sort(p + 1, p + m + 1, [&] (int i, int j) {
		return w[i] < w[j];
	});
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	int L = 1, R = 1;
	while(L <= m){
		while(R <= m and w[p[L]] == w[p[R]]) R += 1;
		vector<int> nodes;
		vector<int> edges;
		getGraph(L, R, nodes, edges);
		for(auto u : nodes){
			if(vis[u]) continue;
			DFS(u);
		}
		for(int i = L; i < R; i++){
			join(a[p[i]], b[p[i]]);
		}
		for(auto e : edges){
			
		}
		for(auto u : nodes){
			vis[u] = 0;
			G[u].clear();
			E[u].clear();
		}
		L = R;
	}
	for(int i=1; i<=m; i++){
		puts(ans[i]? (ans[i] == 1? "at least one" : "any") : "none");
	}
	return 0;
}
