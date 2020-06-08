#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;
const int M = 100000;

int n;
int r[N];
int c[N];
int par[N];
int sizes[N];

void create(int x){
	par[x] = x;
	sizes[x] = 1;
	if(x <= M) r[x] = 1;
	else c[x] = 1;
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
	r[b] += r[a];
	c[b] += c[a];
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=M+M; i++) create(i);
	for(int i=1; i<=n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		join(x, y + M);
	}
	long long ans = -n;
	for(int i=1; i<=M+M; i++){
		if(par[i] == i){
			ans += 1LL * r[i] * c[i];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
