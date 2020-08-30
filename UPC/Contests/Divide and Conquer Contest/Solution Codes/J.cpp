#include<bits/stdc++.h>
using namespace::std;

int n, k;

long long getLines(long long v, long long K){
	if(v < K) return 0;
	return (v / K) + getLines(v , k * K);
}

int main(){
	scanf("%d %d", &n, &k);
	int lo = 0LL, hi = 1000000000;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(getLines(mi, 1) < n) lo = mi + 1;
		else hi = mi;
	}
	printf("%d\n", lo);
	return 0;
}
