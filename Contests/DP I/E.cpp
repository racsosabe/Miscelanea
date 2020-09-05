#include<bits/stdc++.h>
using namespace::std;

const int N = 3000+5;

int n;
int a[N];
bool vis[N][N];
long long memo[N][N];

long long DP(int l, int r){
	if(r < l) return 0LL;
	if(vis[l][r]) return memo[l][r];
	int turn = (n - (r - l + 1)) & 1;
	long long ans;
	if(turn == 0){
		ans = max(a[l] + DP(l + 1, r), a[r] + DP(l, r - 1));
	}
	else{
		ans = min(-a[l] + DP(l + 1, r), -a[r] + DP(l, r - 1));
	}
	vis[l][r] = true;
	return memo[l][r] = ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	printf("%lld\n", DP(0, n - 1));
	return 0;
}

