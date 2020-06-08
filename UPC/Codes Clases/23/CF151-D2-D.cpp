#include<bits/stdc++.h>
using namespace::std;

const int N = 2000+5;
const int MOD = 1000000000 + 7;

int mul(long long a, long long b, int m = MOD){
	return (a * b) % m;
}

int n, m, k;
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
	scanf("%d %d %d", &n, &m, &k);
	for(int i=1; i<=n; i++) create(i);
	for(int i=1; i+k-1<=n; i++){
		for(int l = 0; l <= k - l - 1; l++){
			join(i + l, i + k - l - 1);
		}
	}
	int ans = 1;
	for(int i=1; i<=n; i++){
		if(par[i] == i) ans = mul(ans, m);
	}
	printf("%d\n", ans);
	return 0;
}
