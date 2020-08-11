#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;
const int inf = 2e9;

int n;
int a[N];
int ans[N];
int memo[N];

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
	}
	memo[n] = inf;
	for(int i = n - 1; i >= 0; i--){
		int lo = i, hi = n;
		while(lo < hi){
			int mi = lo + (hi - lo + 1) / 2;
			if(a[i] > memo[mi]) lo = mi;
			else hi = mi - 1;
		}
		if(lo == i) ans[i] = -1;
		else ans[i] = lo - i - 1;
		memo[i] = min(a[i], memo[i+1]);
	}
	for(int i = 0; i < n; i++){
		printf("%d%c", ans[i], " \n"[i + 1 == n]);
	}
	return 0;
}
