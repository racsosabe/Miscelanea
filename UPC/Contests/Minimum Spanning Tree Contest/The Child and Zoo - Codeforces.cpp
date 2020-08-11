#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n, m;
int a[N];
int par[N];
int sizes[N];
vector<int> G[N];

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

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		par[i] = i;
		sizes[i] = 1;
	}
	for(int i = 1; i <= m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return a[i] > a[j];
	});
	double ans = 0.0;
	for(int i : p){
		for(int v : G[i]){
			if(a[i] > a[v]) continue;
			if(get(i) != get(v)){
				ans += 2LL * a[i] * sizes[get(i)] * sizes[get(v)];
				join(i, v);
			}
		}
	}
	ans /= 1LL * n * (n - 1);
	printf("%.9lf\n", ans);
	return 0;
}
