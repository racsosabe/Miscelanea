#include<bits/stdc++.h>
using namespace::std;

int n;

int solve(int a, int b){
	if(b == 0) return 1e7;
	if(b == 1) return a - 1;
	return a / b + solve(b, a % b);
}

int main(){
	scanf("%d", &n);
	int ans = n - 1;
	for(int i = 1; i <= n; i++){
		ans = min(ans, solve(n, i));
	}
	printf("%d\n", ans);
	return 0;
}
