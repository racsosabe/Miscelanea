#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

int n;
int m;
int par[N];
int last[N];
int sizes[N];
vector<iii> edges;

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

int join(int a, int b, int w){
	a = get(a);
	b = get(b);
	if(a == b) return last[a] < w? 1 : 2;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	last[b] = max(last[b], w);
	return 0;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges.emplace_back(make_pair(w, make_pair(u, v)));
	}
	sort(edges.begin(), edges.end());
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
		last[i] = 0;
	}
	int ans = 0;
	int L = 0, R = 0;
	while(L < m){
		while(R < m and edges[L].first == edges[R].first){
			R += 1;
		}
		vector<int> edgesMST;
		for(int i = L; i < R; i++){
			int u = edges[i].second.first;
			int v = edges[i].second.second;
			if(get(u) != get(v)) edgesMST.emplace_back(i);
		}
		for(auto i : edgesMST){
			int u = edges[i].second.first;
			int v = edges[i].second.second;
			int w = edges[i].first;
			int type = join(u, v, w);
			if(type) ans += type - 1;
		}
		L = R;
	}
	printf("%d\n", ans);
	return 0;
}
