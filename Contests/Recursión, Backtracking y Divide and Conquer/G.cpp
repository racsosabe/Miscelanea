#include<bits/stdc++.h>
using namespace::std;

long long l, r;

int digits(long long x){
	if(x < 10) return 1;
	return 1 + digits(x / 10);
}

long long f(long long x){
	if(x < 0) return 0;
	long long p = 1;
	long long ans = 1;
	int len = digits(x);
	for(int i = 0; i + 1 < len; i++){
		long long R = max(1LL, x / (10 * p));
		long long act = (R - 1) * p;
		if((x / p) % 10) act += p;
		else act += x % p + 1;
		ans += act;
		p *= 10;
	}
	return ans;
}

int main(){
	while(scanf("%lld %lld", &l, &r) and l >= 0 and r >= 0){
		printf("%lld\n", f(r) - f(l - 1));
	}
	return 0;
}
