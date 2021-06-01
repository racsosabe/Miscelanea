#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;
const int MOD = 5000000;
const int E = 26;

int n;
int T;
int a[N];
int b[N];
int c[N];
int h[N];
int in[N];
int out[N];
int ans[N];
int nxt[N];
int values[N];
int subtree[N];
vector<int> G[N];
vector<int> libres;
vector<int> my_map[MOD];
vector<int> my_key[MOD];

void assign(int x, int y){
	int id = x % MOD;
	for(int i = 0; i < my_key[id].size(); i++){
		if(my_key[id][i] == x){
			my_map[id][i] = y;
		}
	}
}

int get(int x){
	int id = x % MOD;
	for(int i = 0; i < my_key[id].size(); i++){
		if(my_key[id][i] == x){
			return my_map[id][i];
		}
	}
	return -1;
}

void DFS(int u){
	a[T] = u;
	in[u] = T++;
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		h[v] = h[u] + 1;
		b[v] ^= b[u];
		DFS(v);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[G[u][0]]){
			swap(G[u][i], G[u][0]);
		}
	}
	out[u] = T - 1;
}

int getMax(int mask){
	int L = get(mask);
	return L != -1 ? values[L] : -n;
}

void insert(int mask, int height){
	int L = get(mask);
	int new_height = L != -1 ? max(values[L], height) : height;
	int pos = libres.back();
	libres.pop_back();
	nxt[pos] = L;
	values[pos] = new_height;
	assign(mask, pos);
}

void remove(int mask){
	int L = get(mask);
	assert(L != -1);
	libres.emplace_back(L);
	assign(mask, nxt[L]);
}

void solve(int u, int keep){
	for(int i = 1; i < G[u].size(); i++) solve(G[u][i], 0);
	if(!G[u].empty()) solve(G[u][0], 1);
	int cur = 0;
	insert(b[u], h[u]);
	for(int v : G[u]){
		cur = max(cur, ans[v]);
		if(v == G[u][0]) continue;
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			int my_h = b[at];
			cur = max(cur, h[at] + getMax(my_h) - 2 * h[u]);
			for(int j = 0; j < E; j++){
				int want = my_h ^ (1 << j);
				cur = max(cur, h[at] + getMax(want) - 2 * h[u]);
			}
		}
		for(int i = in[v]; i <= out[v]; i++){
			int at = a[i];
			insert(b[at], h[at]);
		}
	}
	cur = max(cur, getMax(b[u]) - h[u]);
	for(int j = 0; j < E; j++){
		int want = b[u] ^ (1 << j);
		cur = max(cur, getMax(want) - h[u]);
	}
	ans[u] = cur;
	if(!keep){
		for(int i = in[u]; i <= out[u]; i++){
			int at = a[i];
			remove(b[at]);
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		int p;
		scanf("%d", &p);
		char l = getchar();
		while(!isalpha(l)) l = getchar();
		b[i] = c[i] = 1 << (l - 'a');
		G[p].emplace_back(i);
	}
	DFS(1);
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return b[i] < b[j];
	});
	for(int i = 0; i < n; i++){
		if(i == 0 or b[p[i - 1]] != b[p[i]]){
			int id = b[p[i]] % MOD;
			my_key[id].emplace_back(b[p[i]]);
			my_map[id].emplace_back(-1);
		}
	}
	for(int i = 0; i < n; i++) libres.emplace_back(i);
	solve(1, 1);
	for(int i = 1; i <= n; i++){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
