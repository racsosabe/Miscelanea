#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int LOG = 18;

int gcd(int a, int b){ return b == 0? a : gcd(b, a % b);}

int n;
int q;
int a[N];
int ST[N][LOG];
map<int, int> st[4 * N];

void merge(int pos){
	for(auto x : st[2 * pos]){
		st[pos][x.first] += x.second;
	}
	for(auto x : st[2 * pos + 1]){
		st[pos][x.first] += x.second;
	}
}

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos][a[l]] += 1;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	merge(pos);
}

int query(int x, int y, int z, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos][z];
	int mi = (l + r) / 2;
	return query(x, y, z, 2 * pos, l, mi) + query(x, y, z, 2 * pos + 1, mi + 1, r);
}

void buildST(){
	for(int i = 1; i <= n; i++) ST[i][0] = a[i];
	for(int d = 1; 1 << d <= n; d++){
		int dis = 1 << (d - 1);
		for(int i = 1; i + 2 * dis - 1 <= n; i++){
			ST[i][d] = gcd(ST[i][d - 1], ST[i + dis][d - 1]);
		}
	}
}

int queryST(int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1 << k;
	return gcd(ST[l][k], ST[r - dis + 1][k]);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	build();
	buildST();
	scanf("%d", &q);
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		int mcd = queryST(l, r);
		printf("%d\n", r - l + 1 - query(l, r, mcd));
	}
	return 0;
}
