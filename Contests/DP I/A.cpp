#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const long long inf = 1e18;

int n;
int k;
int h[N];
long long memo[N];

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &h[i]);
	for(int i = n - 1; i >= 1; i--){
		memo[i] = inf;
		for(int j = 1; j <= k and i + j <= n; j++){
			memo[i] = min(memo[i], abs(h[i] - h[i + j]) + memo[i + j]);
		}
	}
	printf("%lld\n", memo[1]);
	return 0;
}
