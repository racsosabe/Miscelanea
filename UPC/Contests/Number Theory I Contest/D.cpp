#include<bits/stdc++.h>
using namespace::std;

int q;
long long n, m;

long long gcd(long long a, long long b){
	while(b > 0){
		swap(a,b);
		b %= a;
	}
	return a;
}

int main(){
	scanf("%lld %lld %d",&n,&m,&q);
	int sx, ex;
	long long sy, ey, mcd = gcd(n,m);
	while(q--){
		scanf("%d %lld %d %lld",&sx,&sy,&ex,&ey);
		long long C1 = ((sy - 1) / ((sx == 1? n : m) / mcd)) + 1;
		long long C2 = ((ey - 1) / ((ex == 1? n : m) / mcd)) + 1;
		int side1 = 2LL * sy < (sx == 1? n : m)? -1 : (2LL * sy > (sx == 1? n : m) ? 1 : 0);
		int side2 = 2LL * ey < (ex == 1? n : m)? -1 : (2LL * ey > (ex == 1? n : m) ? 1 : 0);
		bool ans = true;
		if(C1 != C2) ans = false;
		puts(ans?"YES":"NO");
	}
	return 0;
}
