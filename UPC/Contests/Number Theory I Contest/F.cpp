#include<bits/stdc++.h>
using namespace::std;

int d;
long long a, b, c;

int main(){
	scanf("%lld %lld %lld %d",&a,&b,&c,&d);
	if(a > b) swap(a,b);
	if(a > c) swap(a,c);
	if(b > c) swap(b,c);
	long long S1 = max(0LL,a+d-b) + max(0LL,max(a+d,b)+d-c);
	long long S2 = max(0LL, a-b+d) + max(0LL,b+d-c);
	long long S3 = max(0LL,b - (c - d)) + max(0LL,a - (min(c-d,b)-d));
	long long ans = min({S1,S2,S3});
	cout << ans << endl;
	return 0;
}
