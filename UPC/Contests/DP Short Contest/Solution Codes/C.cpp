#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int MAX = 20000 + 5;
const int OFF = 10000 + 2;
const int N = 1000 + 5;

int n;
int a[N];
int memo[2][MAX];

int main(){
	scanf("%d", &n);
	int ans = 0;
	int sum = 0;
	for(int i = 1; i <= n; i++){
		int cur = i & 1;
		int prv = cur ^ 1;
		scanf("%d", &a[i]);
		for(int j = -sum; j <= sum; j++) memo[cur][j + OFF] = 0;
		memo[cur][a[i] + OFF] += 1;
		memo[cur][-a[i] + OFF] += 1;
		for(int j = -sum; j <= sum; j++){
			int val = j + a[i] + OFF;
			memo[cur][val] += memo[prv][j + OFF];
			if(memo[cur][val] >= MOD) memo[cur][val] -= MOD;
			val = j - a[i] + OFF;
			memo[cur][val] += memo[prv][j + OFF];
			if(memo[cur][val] >= MOD) memo[cur][val] -= MOD;
		}
		ans += memo[cur][OFF];
		if(ans >= MOD) ans -= MOD;
		sum += a[i];
	}
	printf("%d\n", ans);
	return 0;
}
