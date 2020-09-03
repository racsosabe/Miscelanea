#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;
const int inf = 2e9;

int n;
long long k;
int a[N], b[N];

bool can(long long x){
	long long needed = 0;
	for(int i = 0; i < n; i++){
		if(x * a[i] > b[i]){
			needed += x * a[i] - b[i];
		}
	}
	return needed <= k;
}

int main(){
	scanf("%d %lld", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
	}
	for(int i = 0; i < n; i++){
		scanf("%d", b + i);
	}
	int lo = 0, hi = inf;
	for(int i = 0; i < n; i++){
		if(hi > (b[i] + k) / a[i] + 1){
			hi = (b[i] + k) / a[i] + 1;
		}
	}
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(can(mi)) lo = mi;
		else hi = mi - 1;
	}
	printf("%d\n", lo);
	return 0;
}
