#include<bits/stdc++.h>
using namespace::std;

const int N = 500000+5;

int n;
int m;
int q;
int a[N];
int b[N];
int w[N];
int par[N];
int vis[N];
bool ans[N];
int sizes[N];
set<int> G[N];

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

bool Cycle(int u, int p = -1){
	vis[u] = 1;
	for(int v : G[u]){
		if(vis[v] == 2 or v == p) continue;
		if(vis[v]) return true;
		if(Cycle(v, u)) return true;
	}
	vis[u] = 2;
	return false;
}

void solveQueries(int l, int r, vector< pair<int, int> > &edges){
	int L = l, R = l;
	while(L < r){
		while(R < r and edges[L].second == edges[R].second){
			R += 1;
		}
		int query = edges[L].second;
		for(int i = L; i < R; i++){
			int e = edges[i].first;
			int u = get(a[e]);
			int v = get(b[e]);
			if(u == v){
				ans[query] = false;
				break;
			}
			if(G[u].count(v)){
				ans[query] = false;
			}
			G[u].emplace(v);
			G[v].emplace(u);
		}
		for(int i = L; i < R; i++){
			int e = edges[i].first;
			int u = get(a[e]);
			int v = get(b[e]);
			if(u == v) break;
			if(!vis[u]){
				if(Cycle(u)){
					ans[query] = false;
				}
			}
		}
		for(int i = L; i < R; i++){
			int e = edges[i].first;
			int u = get(a[e]);
			int v = get(b[e]);
			vis[u] = vis[v] = 0;
			G[u].clear();
			G[v].clear();
		}
		L = R;
	}
}

void print(){
	for(int i=1; i<=n; i++){
		cout << par[i] << " ";
	}
	cout << endl;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++){
		scanf("%d %d %d", &a[i], &b[i], &w[i]);
	}
	scanf("%d", &q);
	vector< pair<int, int> > edgesQueries;
	for(int i=1; i<=q; i++){
		int len;
		ans[i] = true;
		scanf("%d", &len);
		for(int j=0; j<len; j++){
			int id;
			scanf("%d", &id);
			edgesQueries.emplace_back(make_pair(id, i));
		}
	}
	sort(edgesQueries.begin(), edgesQueries.end(), [&] (pair<int, int> a, pair<int, int> b){
		return make_pair(w[a.first], a.second) < make_pair(w[b.first], b.second);
	});
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	vector<int> p(m);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return w[i] < w[j];
	});
	int pos = 0;
	int L = 0, R = 0;
	while(L < edgesQueries.size()){
		while(pos < m and w[p[pos]] < w[edgesQueries[L].first]){
			join(a[p[pos]], b[p[pos]]);
			pos += 1;
		}
		while(R < edgesQueries.size() and w[edgesQueries[L].first] == w[edgesQueries[R].first]){
			R += 1;
		}
		solveQueries(L, R, edgesQueries);
		L = R;
	}
	for(int i=1; i<=q; i++){
		puts(ans[i]?"YES":"NO");
	}
	return 0;
}
