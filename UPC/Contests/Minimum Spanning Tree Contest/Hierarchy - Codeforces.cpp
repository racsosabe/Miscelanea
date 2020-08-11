#include<bits/stdc++.h>
using namespace::std;

const int N = 1000+5;
const int E = 10000+5;

int n;
int m;
int q[N];
int par[N];
vector<int> G[N];
vector<int> W[N];

int Prim(int src){
	for(int i=1; i<=n; i++) par[i] = -1;
	par[src] = 0;
	priority_queue< pair<int, int> > Q;
	Q.emplace(make_pair(0, src));
	while(!Q.empty()){
		int u = Q.top().second;
		Q.pop();
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			int w = W[u][i];
			if(par[v] == -1 or par[v] > w){
				par[v] = w;
				Q.emplace(make_pair(-par[v], v));
			}
		}
	}
	int ans = 0;
	for(int i=1; i<=n; i++){
		if(par[i] == -1) return -1;
		ans += par[i];
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i=1; i <= n; i++){
		scanf("%d", &q[i]);
	}
	scanf("%d", &m);
	for(int i=1; i<=m; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		G[a].emplace_back(b);
		W[a].emplace_back(c);
	}
	int root = 1;
	for(int i=2; i<=n; i++){
		if(q[i] > q[root]) root = i;
	}
	int ans = Prim(root);
	printf("%d\n", ans);
	return 0;
}
