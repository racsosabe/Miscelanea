#include<bits/stdc++.h>
using namespace::std;

long long n, k;

int main(){
	scanf("%lld %lld", &n, &k);
	if(k == 1) printf("%lld\n", n);
	else{
		int pos = 63 - __builtin_clzll(n);
		pos++;
		long long ans = 1LL<<pos;
		ans -= 1;
		printf("%lld\n", ans);
	}
	return 0;
}
