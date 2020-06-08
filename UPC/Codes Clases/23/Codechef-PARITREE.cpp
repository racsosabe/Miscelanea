#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;
const int MOD = 1000000000+7;

int mul(long long a, long long b, int m = MOD){
	return (a * b) % m;
}

int pow_mod(int a, int b, int m = MOD){
	int res = 1;
	while(b > 0){
		if(b & 1) res = mul(res, a, m);
		a = mul(a, a, m);
		b >>= 1;
	}
	return res;
}

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
		for(int i=1; i<n; i++){
			int u, v;
			scanf("%d %d", &u, &v);
		}
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
		int ans = 0;
		bool can = true;
		for(int i=1; i<=2*n; i++){
			if(2 * i - 1 <= 2 * n){
				if(get(2 * i) ==  get(2 * i - 1)) can = false;
			}
			if(par[i] == i) ans += 1;
		}
		ans >>= 1;
		ans = can? pow_mod(2, ans - 1) : 0;
		printf("%d\n", ans);
	}
	return 0;
}
