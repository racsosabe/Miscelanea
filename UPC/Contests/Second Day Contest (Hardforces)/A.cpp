#include<bits/stdc++.h>
using namespace::std;

long long n, k;

int main(){
	scanf("%lld %lld", &n, &k);
	set<long long> S;
	for(long long i = 1; i <= k; i++){
		long long mod = n % i;
		if(S.count(mod)){
			puts("No");
			return 0;
		}
		S.emplace(mod);
	}
	puts("Yes");
	return 0;
}
