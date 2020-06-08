#include<bits/stdc++.h>
using namespace::std;

const int N = 2000+5;
const int MOD = 1000000000+7;

int mul(long long a, long long b, int m = MOD){
	return (a * b) % m;
}

int n;
int m;
int par[N];
int sizes[N];
bool vis[N][N];

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

void update(int l, int r){
	while(l < r and !vis[l][r]){
		join(l, r);
		vis[l][r] = true;
		l += 1;
		r -= 1;
	}
}

void clearAll(){
	for(int i=1; i<=n; i++){
		for(int j=i; j<=n; j++){
			vis[i][j] = false;
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; i++){
			create(i);
			vis[i][i] = true;
		}
		for(int i=1; i<=m; i++){
			int l, r;
			scanf("%d %d", &l, &r);
			update(l, r);
		}
		int ans = 1;
		for(int i=1; i<=n; i++){
			if(par[i] == i) ans = mul(ans, 26);
		}
		printf("%d\n", ans);
		if(t) clearAll();
	}
	return 0;
}
