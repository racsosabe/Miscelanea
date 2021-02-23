#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;
const int M = 1000000 + 5;

int n;
int q;
int a[N];
int D[M];
int maximo[4 * N];
long long st[4 * N];

void init(){
	for(int i = 1; i < M; i++){
		for(int j = i; j < M; j += i) D[j] += 1;
	}
}

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = maximo[pos] = a[l];
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
	maximo[pos] = max(maximo[2 * pos], maximo[2 * pos + 1]);
}

void update(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or maximo[pos] <= 2) return;
	if(l == r){
		st[pos] = maximo[pos] = D[st[pos]];
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, 2 * pos, l, mi);
	update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
	maximo[pos] = max(maximo[2 * pos], maximo[2 * pos + 1]);
}

long long query(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int main(){
	init();
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build();
	while(q--){
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);
		if(op == 1){
			update(l, r);
		}
		else{
			printf("%lld\n", query(l, r));
		}
	}
	return 0;
}
