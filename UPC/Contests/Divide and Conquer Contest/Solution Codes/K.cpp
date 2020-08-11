#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int d;
long long prefix[N];

long long getBest(int L, vector< pair<int,int> > &v){
	int lo = L, hi = n - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(v[mi].first - v[L].first < d) lo = mi;
		else hi = mi - 1;
	}
	return prefix[lo + 1] - prefix[L];
}

int main(){
	scanf("%d %d", &n, &d);
	vector< pair<int,int> > v(n);
	for(int i = 0; i < n; i++){
		scanf("%d %d", &v[i].first, &v[i].second);
	}
	sort(v.begin(), v.end());
	for(int i = 1; i <= n; i++){
		prefix[i] = prefix[i-1] + v[i-1].second;
	}
	long long ans = 0LL;
	for(int i = 0; i < n; i++){
		ans = max(ans,getBest(i, v));
	}
	printf("%lld\n", ans);
	return 0;
}
