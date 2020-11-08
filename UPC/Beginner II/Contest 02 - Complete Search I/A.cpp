#include<bits/stdc++.h>
using namespace::std;

long long n;

int suma(long long x){
	if(x < 10) return x;
	return x % 10 + suma(x / 10);
}

long long test(int sx){
	long long x = sqrt(n);
	while(x * (x + sx) > n) x -= 1;
	if(x * (x + sx) < n) return -1;
	return suma(x) == sx ? x : -1;
}

int main(){
	scanf("%lld", &n);
	long long ans = -1;
	for(int sx = 1; sx <= 9 * 18; sx++){
		long long cand = test(sx);
		if(cand >= 0){
			if(ans > cand or ans == -1) ans = cand;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
