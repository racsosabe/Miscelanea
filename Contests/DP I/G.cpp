#include<bits/stdc++.h>
using namespace::std;

const int N = 400 + 5;
const long long inf = 1e18;

int n;
int a[N];
bool vis[N][N];
long long prefix[N];
long long memo[N][N];

long long getSize(int l, int r){
	if(r <= l) return 0LL;
	return l == 0? prefix[r] : prefix[r] - prefix[l-1];
}

long long DP(int l, int r){
	if(r <= l) return 0LL;
	if(l + 1 == r) return a[l] + a[r];
	if(vis[l][r]) return memo[l][r];
	long long ans = inf;
	for(int k = l; k < r; k++){
		long long cand = DP(l, k) + getSize(l, r) + DP(k + 1, r);
		if(ans > cand){
			ans = cand;
		}
	}
	vis[l][r] = true;
	return memo[l][r] = ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &a[i]);
		prefix[i] = a[i];
		if(i > 0) prefix[i] += prefix[i - 1];
	}
	printf("%lld\n", DP(0, n - 1));
	return 0;
}

