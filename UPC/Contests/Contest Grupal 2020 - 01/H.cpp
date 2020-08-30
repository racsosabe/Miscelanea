#include<bits/stdc++.h>
using namespace::std;

int n, k;

int main(){
	scanf("%d %d", &n, &k);
	int total = 2 * k;
	long long ans = 0LL;
	if(n < total) ans = 10LL;
	else{
		if(n % total){
			ans += (n / total) * 5LL + 5LL;
			n -= total - n % total;
			ans += ((n + total - 1) / total) * 5LL;
		}
		else{
			ans = (n / k) * 5LL;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
