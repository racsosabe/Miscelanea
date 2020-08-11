#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int m;
int q;
int L[N];
int R[N];
int v[N];
int c[N];
long long ft[N];

void update(int pos, long long val){
	pos++;
	while(pos <= n + 1){
		ft[pos] = max(ft[pos], val);
		pos += (-pos) & pos;
	}
}

long long query(int pos){
	pos++;
	long long res = 0LL;
	while(pos > 0){
		res = max(res, ft[pos]);
		pos &= pos - 1;
	}
	return res;
}

int main(){
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= m; i++) scanf("%d", &c[i]);
	for(int i = 1; i <= q; i++){
		scanf("%d %d %d", L + i, R + i, v + i);
		v[i] = c[v[i]];
	}
	vector<int> p(q);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(L[i] == L[j]) return R[i] < R[j];
		return L[i] < L[j];
	});
	long long ans = 0LL;
	for(int i : p){
		long long cur = query(L[i]) + v[i];
		update(R[i], cur);
		ans = max(ans, cur);
	}
	printf("%lld\n", ans);
	return 0;
}
