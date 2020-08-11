#include<bits/stdc++.h>
using namespace::std;

const int N = 1000+5;
const int MOD = 1000000000+7;

int n;
int k;
int g[N];
char s[N];
bool vis[N][N][3];
int memo[N][N][3];

int f(int x){
	if(x == 1) return 0;
	return 1 + f(__builtin_popcount(x));
}

void init(){
	g[0] = -1;
	for(int i=1; i<=1000; i++){
		g[i] = f(i);
	}
}

int DP(int pos, int bits, bool menor){
	if(pos == n){
		return g[bits] == k-1;
	}
	if(vis[pos][bits][menor]) return memo[pos][bits][menor];
	int ans = 0;
	int limit = menor? 1 : s[pos] - '0';
	for(int i = 0; i <= limit; i++){
		ans += DP(pos + 1, bits + i, menor | (i + '0'  < s[pos]));
		if(ans >= MOD) ans -= MOD;
	}
	vis[pos][bits][menor] = true;
	return memo[pos][bits][menor] = ans;
}

int main(){
	scanf("%s", s);
	scanf("%d", &k);
	init();
	n = strlen(s);
	int ans = k > 0? DP(0,0,0) : 1;
	if(k == 1){
		ans -= 1;
		if(ans < 0) ans += MOD;
	}
	printf("%d\n",ans);
	return 0;
}

