#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000+5;

int gcd(int a, int b){ return b == 0? a : gcd(b, a % b);}

int n, k;
int a[N];

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	int mcd = 0;
	for(int i = 1; i <= k; i++){
		int x;
		scanf("%d", &x);
		mcd = gcd(mcd, x);
	}
	for(int i = 1; i + 1 <= n; i++){
		int dif = abs(a[i + 1] - a[i]);
		if(dif % mcd){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}
