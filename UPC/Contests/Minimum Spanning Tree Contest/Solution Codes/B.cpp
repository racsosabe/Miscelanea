#include<bits/stdc++.h>
using namespace::std;

const int N = 10000+5;
const int M = 100000+5;

int n, m;
int minedge[N];
long long D[N];
vector<int> G[N];
vector<int> L[N];
vector<int> C[N];

void addEdge(int a, int b, int l, int c){
	G[a].emplace_back(b);
	L[a].emplace_back(l);
	C[a].emplace_back(c);
}

long long Prim(int src){
	for(int i=1; i<=n; i++){
		D[i] = 1e15;
		minedge[i] = 1e9 + 5;
	}
	D[src] = 0;
	minedge[src] = 0;
	priority_queue< pair<long long, pair<int, int> > > Q;
	Q.emplace(make_pair(-D[src], make_pair(-minedge[src], src)));
	while(!Q.empty()){
		long long dis = -Q.top().first;
		int minimum = -Q.top().second.first;
		int u = Q.top().second.second;
		Q.pop();
		if(make_pair(D[u], minedge[u]) < make_pair(dis, minimum)) continue;
		for(int i=0; i<G[u].size(); i++){
			int v = G[u][i];
			int len = L[u][i];
			int cost = C[u][i];
			if(D[v] > dis + len){
				D[v] = dis + len;
				minedge[v] = cost;
				Q.emplace(make_pair(-D[v], make_pair(-minedge[v], v)));
			}
			else if(D[v] == dis + len){
				if(minedge[v] > cost){
					minedge[v] = cost;
					Q.emplace(make_pair(-D[v], make_pair(-minedge[v], v)));
				}
			}
		}
	}
	long long ans = 0LL;
	for(int i=1; i<=n; i++){
		ans += minedge[i];
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int u, v, l, c;
		scanf("%d %d %d %d", &u, &v, &l, &c);
		addEdge(u, v, l, c);
		addEdge(v, u, l, c);
	}
	printf("%lld\n", Prim(1));
	return 0;
}
