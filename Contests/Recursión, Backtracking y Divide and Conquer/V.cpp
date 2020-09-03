#include<bits/stdc++.h>
using namespace::std;

struct node{
	long long sum;
	long long ans;
	long long prefix;
	long long suffix;
	node(){};
	node(long long sum, long long ans, long long prefix, long long suffix) :
		sum(sum), ans(ans), prefix(prefix), suffix(suffix) {};
};

const int N = 250000+5;
const long long inf = 1e18;

int n;
int m;
int id[N];
long long sum[N];
long long ans[N];
long long prefix[N];
long long suffix[N];

void parse(int p, vector<long long> v, int q){
	ans[p] = -inf;
	sum[p] = 0;
	prefix[p] = suffix[p] = -inf;
	long long minimo = 0LL, prefijo = 0LL;
	for(int i = 0; i < q; i++){
		sum[p] += v[i];
		prefijo += v[i];
		ans[p] = max(ans[p], prefijo - minimo);
		minimo = min(minimo, prefijo);
		prefix[p] = max(prefix[p], prefijo);
	}
	for(int i = q - 1; i >= 0; i--){
		if(i + 1 < q) v[i] += v[i + 1];
		suffix[p] = max(suffix[p], v[i]);
	}
}

node merge(node a, node b){
	node q;
	q.sum = a.sum + b.sum;
	q.ans = max({a.ans, b.ans, a.suffix + b.prefix});
	q.prefix = max(a.prefix, a.sum + b.prefix);
	q.suffix = max(b.suffix, b.sum + a.suffix);
	return q;
}

node solve(int l, int r){
	if(l == r){
		return node(sum[id[l]], ans[id[l]], prefix[id[l]], suffix[id[l]]);
	}
	int mi = (l + r) / 2;
	node L = solve(l, mi);
	node R = solve(mi + 1, r);
	return merge(L, R);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		int q;
		scanf("%d", &q);
		vector<long long> v(q);
		for(int j = 0; j < q; j++){
			scanf("%lld", &v[j]);
		}
		parse(i, v, q);
	}
	for(int i = 1; i <= m; i++){
		scanf("%d", &id[i]);
	}
	node ans = solve(1, m);
	printf("%lld\n", ans.ans);
	return 0;
}
