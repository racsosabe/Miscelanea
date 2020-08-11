#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000+5;

struct node{
	int abren;
	int cierran;
	long long ans;
	node(){};
	node(char c){
		abren = c == '(';
		cierran = c == ')';
		ans = 0LL;
	}
};

int n;
int q;
node NIL;
char s[N];
node st[4 * N];

node merge(node a, node b){
	node q;
	q.ans = a.ans + b.ans;
	int extra = min(a.abren, b.cierran);
	q.ans += extra;
	q.abren = a.abren + b.abren - extra;
	q.cierran = a.cierran + b.cierran - extra;
	return q;
}

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = node(s[l]);
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = merge(st[2 * pos], st[2 * pos + 1]);
}

node query(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return NIL;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return merge(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	build();
	scanf("%d", &q);
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%lld\n", 2LL * query(l, r).ans);
	}
	return 0;
}
