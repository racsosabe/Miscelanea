#include<bits/stdc++.h>
using namespace::std;

int n, m;
long long k;

long long getCount(long long x){
	long long ans = 0LL;
	for(int i=1; i<=n; i++){
		ans += min(1LL * m, x / i);
	}
	return ans;
}

int main(){
	scanf("%d %d %lld", &n, &m, &k);
	long long lo = 1, hi = 1LL * n * m;
	while(lo < hi){
		long long mi = lo + (hi-lo)/2;
		if(getCount(mi) < k) lo = mi + 1;
		else hi = mi;
	}
	printf("%lld\n", lo);
	return 0;
}

