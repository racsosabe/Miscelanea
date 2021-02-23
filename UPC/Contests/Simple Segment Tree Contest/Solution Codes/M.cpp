#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int LOG = 10;
const int MOD = 4001;

int add(int a, int b, int m = MOD){
	return (a + b) % m;
}

int mul(int a, int b, int m = MOD){
	return (a * b) % m;
}

struct node{
	int pones;
	int sones;
	int pzeros;
	int szeros;
	int total;
	int ans;
	node(){};
	node(int x){
		pones = x == 1;
		sones = x == 1;
		pzeros = x == 0;
		szeros = x == 0;
		total = x;
		ans = x == 1;
	}
};

int n;
int q;
int a[N];
node NIL;
node st[LOG][4 * N];

node merge(node a, node b){
	node q;
	q.ans = add(a.ans, add(b.ans, add(mul(a.sones, b.pzeros), mul(a.szeros, b.pones))));
	q.pones = add(a.pones, (a.total? b.pzeros : b.pones));
	q.pzeros = add(a.pzeros, (a.total? b.pones : b.pzeros));
	q.sones = add(b.sones, (b.total? a.szeros : a.sones));
	q.szeros = add(b.szeros, (b.total? a.sones : a.szeros));
	q.total = a.total ^ b.total;
	return q;
}

void build(int id, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[id][pos] = node((a[l] >> id) & 1);
		return;
	}
	int mi = (l + r) / 2;
	build(id, 2 * pos, l, mi);
	build(id, 2 * pos + 1, mi + 1, r);
	st[id][pos] = merge(st[id][2 * pos], st[id][2 * pos + 1]);
}

void update(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[id][pos] = node(y);
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(id, x, y, 2 * pos, l, mi);
	else update(id, x, y, 2 * pos + 1, mi + 1, r);
	st[id][pos] = merge(st[id][2 * pos], st[id][2 * pos + 1]);
}

node query(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return NIL;
	if(x <= l and r <= y) return st[id][pos];
	int mi = (l + r) / 2;
	return merge(query(id, x, y, 2 * pos, l, mi), query(id, x, y, 2 * pos + 1, mi + 1, r));
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < LOG; i++) build(i);
	while(q--){
		int op, l, r;
		scanf("%d %d %d", &op, &l, &r);
		if(op == 1){
			for(int i = 0; i < LOG; i++){
				update(i, l, (r >> i) & 1);
			}
		}
		else{
			int ans = 0;
			for(int i = 0; i < LOG; i++){
				ans = add(ans, mul((1LL << i), query(i, l, r).ans));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
