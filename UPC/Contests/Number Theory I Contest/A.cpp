#include<bits/stdc++.h>
using namespace::std;

long long n, k;

long long solve(long long a, long long b){
	if(a < b) return a;
	return a % b + solve(a / b, b) + 1;
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%lld %lld",&n,&k);
		long long ans = solve(n,k);
		printf("%lld\n",ans);
	}
	return 0;
}
