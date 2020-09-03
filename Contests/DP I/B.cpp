#include<bits/stdc++.h>
using namespace::std;

const int MAX = 100000 + 5;
const int inf = 1e9 + 10;

int n;
int C;
int memo[MAX];

int main(){
	scanf("%d %d", &n, &C);
	int sum = 0;
	for(int i = 1; i < MAX; i++) memo[i] = inf;
	for(int i = 1; i <= n; i++){
		int w, v;
		scanf("%d %d", &w, &v);
		sum += v;
		for(int j = sum; j >= v; j--){
			memo[j] = min(memo[j], w + memo[j - v]);
		}
	}
	int ans = 0;
	for(int i = 1; i <= sum; i++){
		if(memo[i] <= C) ans = i;
	}
	printf("%d\n", ans);
	return 0;
}
