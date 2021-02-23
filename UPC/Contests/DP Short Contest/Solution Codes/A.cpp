#include<bits/stdc++.h>
using namespace::std;

const int N = 50 + 5;

int n;
char s[N][N];
bool vis[N][N][N][N];
int memo[N][N][N][N];

int DP(int x1, int y1, int x2, int y2){
	if(x1 == x2 and y1 == y2) return s[x1][y1] == '#';
	if(vis[x1][y1][x2][y2]) return memo[x1][y1][x2][y2];
	int ans = max(x2 - x1, y2 - y1) + 1;
	for(int i = x1; i < x2; i++){
		ans = min(ans, DP(x1, y1, i, y2) + DP(i + 1, y1, x2, y2));
	}
	for(int i = y1; i < y2; i++){
		ans = min(ans, DP(x1, y1, x2, i) + DP(x1, i + 1, x2, y2));
	}
	vis[x1][y1][x2][y2] = true;
	return memo[x1][y1][x2][y2] = ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%s", s[i] + 1);
	}
	printf("%d\n", DP(1, 1, n, n));
	return 0;
}
