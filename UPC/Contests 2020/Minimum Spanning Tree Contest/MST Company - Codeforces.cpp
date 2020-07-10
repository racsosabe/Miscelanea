#include<bits/stdc++.h>
using namespace::std;

const int M = 100000+5;
const int N = 5000+5;

int n;
int m;
int k;
int a[M];
int b[M];
int w[M];
int par[N];
int sizes[N];
vector<int> p;
vector<int> ones;
vector<int> edges;

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

bool join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return false;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	return true;
}

void init(){
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
}

int can(int adding){
	init();
	for(auto e : ones){
		w[e] += adding;
	}
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(w[i] == w[j]) return a[i] == 1;
		return w[i] < w[j];
	});
	edges.clear();
	int degree = 0;
	for(auto i : p){
		int u = a[i];
		int v = b[i];
		if(join(u, v)){
			if(u == 1) degree += 1;
			edges.emplace_back(i);
		}
	}
	for(auto e : ones){
		w[e] -= adding;
	}
	return degree;
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i=1; i<=m; i++){
		scanf("%d %d %d", &a[i], &b[i], &w[i]);
		w[i] <<= 1;
		if(a[i] > b[i]) swap(a[i], b[i]);
		if(a[i] == 1) ones.emplace_back(i);
		p.emplace_back(i);
	}
	int lo = -2e5, hi = 2e5;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(can(mi) >= k) lo = mi;
		else hi = mi-1;
	}
	if(can(lo) != k) puts("-1");
	else{
		printf("%d\n", n - 1);
		for(int i=0; i+1<n; i++){
			printf("%d%c", edges[i], " \n"[i + 2 == n]);
		}
	}
	return 0;
}
