#include<bits/stdc++.h>
using namespace::std;

const int N = 2000000+5;

int n, m;
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
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &m);
		for(int i=1; i<=2*n; i++) create(i);
		for(int i=1; i<=m; i++){
			int u, v, x;
			scanf("%d %d %d", &u, &v, &x);
			if(x == 0){
				join(2 * u, 2 * v);
				join(2 * u - 1, 2 * v - 1);
			}
			else{
				join(2 * u, 2 * v - 1);
				join(2 * u - 1, 2 * v);
			}
		}
		bool can = true;
		for(int i=1; i<=n; i++){
			if(get(2 * i) == get(2 * i - 1)) can = false;
		}
		puts(can?"yes":"no");
	}
	return 0;
}
