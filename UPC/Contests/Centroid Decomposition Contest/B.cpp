#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int h[N];
int subtree[N];
bool removed[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		DFS(v, u);
		subtree[u] += subtree[v];
	}
}

int centroid(int u, int p, int root){
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		if(2 * subtree[v] > subtree[root]) return centroid(v, u, root);
	}
	return u;
}

void decompose(int u, int depth = 0){
	DFS(u);
	int c = centroid(u, u, u);
	removed[c] = true;
	h[c] = depth;
	for(int v : G[c]){
		if(removed[v]) continue;
		decompose(v, depth + 1);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	decompose(1);
	for(int i = 1; i <= n; i++){
		printf("%c%c", char('A' + h[i]), " \n"[i == n]);
	}
	return 0;
}
