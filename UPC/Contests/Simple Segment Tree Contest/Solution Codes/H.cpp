#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;
const int LOG = 20;

int n;
int q;
int a[N];
int st[LOG][4 * N];
int lazy[LOG][4 * N];

void push(int id, int pos, int l, int r){
	if(lazy[id][pos]){
		st[id][pos] = r - l + 1 - st[id][pos];
		if(l < r){
			lazy[id][2 * pos] ^= lazy[id][pos];
			lazy[id][2 * pos + 1] ^= lazy[id][pos];
		}
		lazy[id][pos] = 0;
	}
}

void build(int id, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[id][pos] = (a[l] >> id) & 1;
		return;
	}
	int mi = (l + r) / 2;
	build(id, 2 * pos, l, mi);
	build(id, 2 * pos + 1, mi + 1, r);
	st[id][pos] = st[id][2 * pos] + st[id][2 * pos + 1];
}

void update(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	push(id, pos, l, r);
	if(y < l or r < x or x > y) return;
	if(x <= l and r <= y){
		lazy[id][pos] ^= 1;
		push(id, pos, l, r);
		return;
	}
	int mi = (l + r) / 2;
	update(id, x, y, 2 * pos, l, mi);
	update(id, x, y, 2 * pos + 1, mi + 1, r);
	st[id][pos] = st[id][2 * pos] + st[id][2 * pos + 1];
}

int query(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	push(id, pos, l, r);
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[id][pos];
	int mi = (l + r) / 2;
	return query(id, x, y, 2 * pos, l, mi) + query(id, x, y, 2 * pos + 1, mi + 1, r);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < LOG; i++) build(i);
	scanf("%d", &q);
	while(q--){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int l, r;
			scanf("%d %d", &l, &r);
			long long ans = 0LL;
			for(int i = 0; i < LOG; i++){
				ans += (1LL<<i) * query(i, l, r);
			}
			printf("%lld\n", ans);
		}
		else{
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);
			for(int i = 0; i < LOG; i++){
				if(x & (1<<i)){
					update(i, l, r);
				}
			}
		}
	}
	return 0;
}
