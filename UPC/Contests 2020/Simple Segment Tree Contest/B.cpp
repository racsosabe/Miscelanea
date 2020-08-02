#include<bits/stdc++.h>
using namespace::std;

const int N = 300000+5;

int n;
int m;
int st[4 * N];

void update(int x, int y, int z, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return;
	if(st[pos]) return;
	if(l == r){
		if(l != z) st[pos] = z;
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, z, 2 * pos, l, mi);
	update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = min(st[2 * pos], st[2 * pos + 1]);
}

int query(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return n+1;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return min(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

int main(){
	scanf("%d %d", &n, &m);
	while(m--){
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
		update(l, r, x);
	}
	for(int i = 1; i <= n; i++){
		printf("%d%c", query(i, i), " \n"[i == n]);
	}
	return 0;
}
