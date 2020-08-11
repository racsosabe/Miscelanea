#include<bits/stdc++.h>
using namespace::std;

int A, B, n;

bool can(int l, int r, int t,  int m){
	long long total = 1LL * t * m;
	long long sum = 1LL * (r - l + 1) * A + (1LL * r * (r - 1) / 2LL - 1LL * (l - 1) * (l - 2) / 2LL) * B;
	long long maximo = A + 1LL * (r - 1) * B;
	return sum <= total and maximo <= t;
}

int main(){
	scanf("%d %d %d", &A, &B, &n);
	while(n--){
		int l, t, m;
		scanf("%d %d %d", &l, &t, &m);
		int lo = l, hi = 2e6;
		while(lo < hi){
			int mi = lo + (hi - lo + 1) / 2;
			if(can(l, mi, t, m)) lo = mi;
			else hi = mi - 1;
		}
		if(!can(l, lo, t, m)) puts("-1");
		else printf("%d\n", lo);
	}
	return 0;
}
