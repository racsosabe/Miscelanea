#include<bits/stdc++.h>
using namespace::std;

const int N = (1 << 17) + 2;

int n;
int q;
int a[N];
int st[4 * N];
int type[4 * N];

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = a[l];
		type[pos] = 1;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	type[pos] = 1 ^ type[2 * pos];
	st[pos] = type[pos]? st[2 * pos] ^ st[2 * pos + 1] : st[2 * pos] | st[2 * pos + 1];
}

void update(int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = type[pos]? st[2 * pos] ^ st[2 * pos + 1] : st[2 * pos] | st[2 * pos + 1];
}

int main(){
	scanf("%d %d", &n, &q);
	n = 1 << n;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build();
	while(q--){
		int p, b;
		scanf("%d %d", &p, &b);
		update(p, b);
		printf("%d\n", st[1]);
	}
	return 0;
}
