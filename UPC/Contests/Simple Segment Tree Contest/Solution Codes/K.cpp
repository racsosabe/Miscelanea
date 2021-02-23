#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int q;
int p[N];
int L[N];
int id[N];
int ans[N];
int st[4 * N];
vector<int> Q[N];
vector<int> I[N];

void init(){
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j += i){
			int l = id[i];
			int r = id[j];
			if(l > r) swap(l, r);
			I[r].emplace_back(l);
		}
	}
}

void update(int x, int y, int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] += y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

int query(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

void download(int r){
	while(!I[r].empty()){
		int l = I[r].back();
		I[r].pop_back();
		update(l, 1);
	}
}

void solve(int r){
	for(auto x : Q[r]){
		int l = L[x];
		ans[x] = query(l, r);
	}
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++){
		scanf("%d", p + i);
		id[p[i]] = i;
	}
	for(int i = 1; i <= q; i++){
		int r;
		scanf("%d %d",L + i, &r);
		Q[r].emplace_back(i);
	}
	init();
	for(int i = 1; i <= n; i++){
		download(i);
		solve(i);
	}
	for(int i = 1; i <= q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
