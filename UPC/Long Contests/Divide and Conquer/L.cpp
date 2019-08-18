#include<bits/stdc++.h>
using namespace::std;

/*
	Problem: Burning Midnight Oil - Codeforces 165B

	Author: Racso Galvan
*/

int n, k;

long long getLines(long long v, long long K){
	if(v < K) return 0;
	return (v / K) + getLines(v , k * K);
}

int main(){
	scanf("%d %d",&n,&k);
	long long lo = 0LL, hi = 1000000000LL;
	while(lo < hi){
		long long mi = lo + (hi-lo)/2;
		if(getLines(mi,1LL) < 1LL * n) lo = mi+1;
		else hi = mi;
	}
	cout << lo << endl;
	return 0;
}
