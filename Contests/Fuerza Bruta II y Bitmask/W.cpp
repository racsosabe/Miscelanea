#include<bits/stdc++.h>
using namespace::std;

int n;
long long k;

int solve(long long L, long long R, int val){
	long long mid = (L + R)/2;
	if(mid == k) return val;
	if(mid < k) return solve(mid + 1, R, val - 1);
	else return solve(L, mid - 1, val - 1);
}

int main(){
	scanf("%d %lld", &n, &k);
	printf("%d\n",solve(1, (1LL << n) - 1, n));
	return 0;
}
