#include<bits/stdc++.h>
using namespace::std;

int a, b;

int main(){
	scanf("%d %d", &a, &b);
	if(a > b) swap(a, b);
	long long ans = 1;
	for(int i = 2; i <= a; i++) ans *= i;
	printf("%lld\n", ans);
	return 0;
}
