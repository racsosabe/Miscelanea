#include<bits/stdc++.h>
using namespace::std;
 
int n;
int a;
int b;
int c;
int d;
 
int getAns(int x){
	int UR = x + b - c;
	int DL = x + a - d;
	int DR = a + UR - d;
	if(UR < 1 or UR > n) return 0;
	if(DL < 1 or DL > n) return 0;
	if(DR < 1 or DR > n) return 0;
	return n;
}
 
int main(){
	scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
	long long ans = 0LL;
	for(int i=1; i<=n; i++){
		ans += getAns(i);
	}
	printf("%lld\n", ans);
	return 0;
}
