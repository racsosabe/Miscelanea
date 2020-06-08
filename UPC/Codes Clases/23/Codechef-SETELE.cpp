#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int a[N];
int b[N];
int w[N];
int par[N];
int sizes[N];

void create(int x){
	par[x] = x;
	sizes[x] = 1;
}

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
	scanf("%d", &n);
	long long S = 0LL;
	for(int i=1; i<n; i++){
		scanf("%d %d %d", &a[i], &b[i], &w[i]);
		S += w[i];
	}
	vector<int> p(n - 1);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return w[i] < w[j];
	});
	for(int i=1; i<=n; i++) create(i);
	double ans = 0LL;
	for(int i : p){
		ans += 1.0 * (S - w[i]) * sizes[get(a[i])] * sizes[get(b[i])];
		join(a[i], b[i]);
	}
	ans /= 1.0 * n * (n - 1) / 2;
	printf("%.9lf\n", ans);
	return 0;
}
