#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;
const int LOG = 18;

int n, m, d;
int x[N];
int c[N];
int ST[N][LOG];

int query(int l, int r){
	int d = r - l + 1;
	int k = 31 - __builtin_clz(d);
	int dis = 1<<k;
	return min(ST[l][k], ST[r - dis + 1][k]);
}

long long solve(vector<int> &orden){
	for(int i = 0; i < orden.size(); i++){
		if(x[orden[i]] - (i ? x[orden[i - 1]] : 0) > n) return -1;
	}
	for(int i = 0; i < orden.size(); i++){
		ST[i][0] = c[orden[i]];
	}
	for(int d = 1; 1<<d <= orden.size(); d++){
		int dis = 1<<(d - 1);
		for(int i = 0; i + 2 * dis - 1 < orden.size(); i++){
			ST[i][d] = min(ST[i][d - 1], ST[i + dis][d - 1]);
		}
	}
	int have = n - x[orden[0]];
	long long ans = 0LL;
	for(int i = 0; i + 1 < orden.size(); i++){
		int lo = i + 1;
		int hi = orden.size() - 1;
		while(lo < hi){
			int mi = lo + (hi - lo) / 2;
			if(query(i + 1, mi) > c[orden[i]]) lo = mi + 1;
			else hi = mi;
		}
		int need = min(n, x[orden[lo]] - x[orden[i]]);
		if(have < need){
			ans += 1LL * (need - have) * c[orden[i]];
			have = need;
		}
		have -= x[orden[i + 1]] - x[orden[i]];
	}
	return ans;
}

int main(){
	scanf("%d %d %d", &d, &n, &m);
	for(int i = 0; i < m; i++){
		scanf("%d %d", &x[i], &c[i]);
	}
	x[m] = d;
	c[m] = 0;
	vector<int> p(m + 1);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return x[i] < x[j];
	});
	printf("%lld\n", solve(p));
	return 0;
}
