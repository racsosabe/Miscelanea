#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;

int n;
int a[N];
int ans[N];
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
	for(int i=1; i<=n; i++) scanf("%d", &a[i]);
	for(int i=1; i<=n; i++) create(i);
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return a[i] > a[j];
	});
	for(int i : p){
		if(i - 1 >= 1 and a[i-1] >= a[i]) join(i - 1, i);
		if(i + 1 <= n and a[i+1] >= a[i]) join(i + 1, i);
		int len = sizes[get(i)];
		ans[len] = max(a[i], ans[len]);
	}
	for(int i=n-1; i>=1; i--){
		ans[i] = max(ans[i], ans[i+1]);
	}
	for(int i=1; i<=n; i++){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
