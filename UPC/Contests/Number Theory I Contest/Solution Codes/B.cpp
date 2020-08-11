#include<bits/stdc++.h>
using namespace::std;

long long gcd(long long a, long long b){
	while(b > 0){
		swap(a,b);
		b %= a;
	}
	return a;
}

int n;
long long mcd = 0LL;

int getDivisors(long long x){
	int ans = 0;
	for(int i = 1; 1LL * i * i <= x; i++){
		if(x % i == 0){
			ans += 1;
			if(1LL * i * i != x) ans += 1;
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	long long x;
	for(int i=1; i<=n; i++){
		scanf("%lld",&x);
		mcd = gcd(mcd,x);
	}
	printf("%d\n",getDivisors(mcd));
	return 0;
}
