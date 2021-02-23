#include<bits/stdc++.h>
using namespace::std;

const int N = 400000 + 5;

int n;
int len;
int a[N];
int b[N];
int w[N];
int st[4 * N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++){
		S.emplace(a[i]);
		S.emplace(b[i]);
	}
	int last = 0;
	map<int, int> id;
	for(auto x : S){
		if(last + 1 < x){
			w[len] = x - 1 - last;
			len += 1;
		}
		id[x] = len;
		w[len] = 1;
		len += 1;
		last = x;
	}
	for(int i = 1; i <= n; i++){
		a[i] = id[a[i]];
		b[i] = id[b[i]];
	}
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

int query(int x, int y, int pos = 1, int l = 0, int r = len - 1){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", a + i, b + i);
	}
	compress();
	vector<int> p(len);
	iota(p.begin(), p.end(), 0);
	for(int i = 1; i <= n; i++){
		swap(p[a[i]], p[b[i]]);
	}
	long long ans = 0LL;
	for(int i = len - 1; i >= 0; i--){
		ans += 1LL * w[p[i]] * query(0, p[i] - 1);
		update(p[i], w[p[i]]);
	}
	printf("%lld\n", ans);
	return 0;
}
