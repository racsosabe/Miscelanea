#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000+5;

int n;
int len;
int a[N];
int b[N];
long long st[4 * N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++){
		S.emplace(a[i]);
	}
	map<int, int> id;
	for(int x : S){
		id[x] = len++;
	}
	for(int i = 1; i <= n; i++){
		a[i] = id[a[i]];
	}
}

void build(int pos = 1, int l = 0, int r = len - 1){
	if(l == r){
		st[pos] = 0;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

void update(int x, int y, int pos = 1, int l = 0, int r = len - 1){
	if(l == r){
		st[pos] += y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

long long query(int x, int y, int pos = 1, int l = 0, int r = len - 1){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	compress();
	for(int i = n; i >= 1; i--){
		b[i] = query(0, a[i] - 1);
		update(a[i], 1);
	}
	build();
	long long ans = 0LL;
	for(int i = n; i >= 1; i--){
		ans += query(1, a[i] - 1);
		update(a[i], b[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
