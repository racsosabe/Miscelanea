#include<bits/stdc++.h>
using namespace::std;

void setIO(string s, bool input = true, bool output = true){
	string inputname = s + ".in";
	string outputname = s + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 100000 + 5;

int n;
int m;
int T;
int t[N];
int h[N];
int v[N];
int L[N];
int R[N];
int w[N];
int ft[N];
int in[N];
int par[N];
int nxt[N];
int subtree[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int i = 0; i + (p != -1) < G[u].size(); i++){
		if(G[u][i] == p) swap(G[u][i], G[u].back());
		int v = G[u][i];
		DFS(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][0], G[u][i]);
		}
	}
	if(p != -1) G[u].pop_back();
}

void HLD(int u){
	v[T] = t[u];
	in[u] = T++;
	for(int v : G[u]){
		h[v] = h[u] + 1;
		par[v] = u;
		nxt[v] = v == G[u][0] ? nxt[u] : v;
		HLD(v);
	}
}

void update(int pos, int val){
	pos++;
	while(pos <= n){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int query(int pos){
	int res = 0;
	pos += 1;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

void change(int a, int b){
	while(nxt[a] != nxt[b]){
		if(h[nxt[a]] < h[nxt[b]]) swap(a, b);
		update(in[nxt[a]], 1);
		update(in[a] + 1, -1);
		a = par[nxt[a]];
	}
	if(h[a] > h[b]) swap(a, b);
	update(in[a] + 1, 1);
	update(in[b] + 1, -1);
}

int main(){
	setIO("grassplant");
	scanf("%d %d", &n, &m);
	for(int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		if(a > b) swap(a, b);
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	DFS(1);
	HLD(1);
	int a, b;
	while(m--){
		char op = getchar();
		while(!isalpha(op)) op = getchar();
		scanf("%d %d", &a, &b);
		if(op == 'P'){
			change(a, b);
		}
		else{
			if(h[a] < h[b]) swap(a, b);
			printf("%d\n", query(in[a]));
		}
	}
	return 0;
}

