#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

int n;
int a[N];
int h[N];
int subtree[N];
vector<int> G[N];

void DFS(int u){
	h[u] ^= a[u];
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] == p) swap(G[u][i], G[u].back());
		int v = G[u][i];
		if(v == p) continue;
		h[v] ^= h[u];
		DFS(v);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][i], G[u][0]);
		}
	}
}



void solve(int u, int keep){
	
}

int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		scanf("%d", &p);
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		a[i] = 1 << (c - 'a');
		G[p].emplace_back(i);
	}
	DFS(1);
	return 0;
}
