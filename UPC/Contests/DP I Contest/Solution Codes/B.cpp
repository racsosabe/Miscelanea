#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;
const int M = 60000+5;

int n, r;
int a[N];
int b[N];
vector<int> p;
int memo[N][M];
bool vis[N][M];

int DP(int pos, int r){
	if(pos == n) return 0;
	if(vis[pos][r]) return memo[pos][r];
	int ans = DP(pos + 1, r);
	if(r >= a[p[pos]] and r + b[p[pos]] >= 0){
		ans = max(ans, 1 + DP(pos + 1, r + b[p[pos]]));
	}
	vis[pos][r] = true;
	return memo[pos][r] = ans;
}

int main(){
	scanf("%d %d", &n, &r);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", a + i, b + i);
	}
	p.resize(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(b[i] >= 0 and b[j] < 0) return true;
		if(b[i] < 0 and b[j] >= 0) return false;
		if(b[i] < 0){
			return max(a[i], -b[i]) + b[i] > max(a[j], -b[j]) + b[j];
		}
		else{
			return a[i] < a[j];
		}
	});
	printf("%d\n", DP(0, r));
	return 0;
}
