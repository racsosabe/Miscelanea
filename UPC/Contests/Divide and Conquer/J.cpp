#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int C;
bool vis[N];
int level[N];
int parent[N];
int subtree[N];
vector<int> G[N];
vector<int> T[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int v : G[u]){
		if(vis[v]) continue;
		if(v != p){
			DFS(v,u);
			subtree[u] += subtree[v];
		}
	}
}

int FindCentroid(int u, int p, int root){
	for(int v : G[u]){
		if(vis[v]) continue;
		if(v != p and subtree[v] > subtree[root] / 2){
			return FindCentroid(v,u,root);
		}
	}
	return u;
}

void decompose(int root, int p = -1){
	DFS(root, root);
	int centroid = FindCentroid(root, root, root);
	if(p == -1) C = centroid;
	else{
		T[p].emplace_back(centroid);
	}
	vis[centroid] = true;
	parent[centroid] = p;
	for(int v : G[centroid]){
		if(vis[v]) continue;
		decompose(v, centroid);
	}
}

void DFS2(int u, int p = 0){
	for(int v : T[u]){
		if(v != p){
			level[v] = level[u]+1;
			DFS2(v,u);
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	decompose(1);
	level[C] = 0;
	DFS2(C);
	for(int i = 1; i <= n; i++){
		printf("%c%c", 'A' + level[i], " \n"[i == n]);
	}
	return 0;

}
