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
	long long ans = 0LL;
	int len = digits(x);
	for(int i = 0; i < len; i++){
		for(int j = 1; j < 10; j++){
			long long act = (x / (10 * p));
			if(j <= (x / p) % 10) act += 1;
			ans += act * j;
		}
		p *= 10;
	}
	return ans;
}

int main(){
	while(scanf("%lld %lld", &l, &r) == 2 and l >= 0 and r >= 0){
		printf("%lld\n", f(r) - f(l - 1));
	}
	return 0;
}
