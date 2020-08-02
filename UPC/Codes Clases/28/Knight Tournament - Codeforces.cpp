#include<bits/stdc++.h>
using namespace::std;

const int N = 300000+5;

int n;
int m;
int st[4*N];

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = 0;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = min(st[2 * pos], st[2 * pos + 1]);
}

void update(int x, int y, int z, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x) return; // Clasica
	if(st[pos] > 0) return; // Todos están cubiertos
	if(l == r){
		if(l != z) st[pos] = z;
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, z, 2 * pos, l, mi);
	update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = min(st[2 * pos], st[2 * pos + 1]);
}

int query(int x, int pos = 1, int l = 1, int r = n){
	if(l == r){
		return st[pos];
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) return query(x, 2 * pos, l, mi);
	else return query(x, 2 * pos + 1, mi + 1, r);
}

int main(){
	scanf("%d %d", &n, &m);
	build();
	for(int i = 1; i <= m; i++){
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		update(l, r, x);
	}
	for(int i = 1; i <= n; i++){
		printf("%d%c", query(i), " \n"[i == n]);
	}
	return 0;
}
