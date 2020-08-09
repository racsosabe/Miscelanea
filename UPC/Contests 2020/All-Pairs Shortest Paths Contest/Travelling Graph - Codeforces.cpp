#include<bits/stdc++.h>
using namespace::std;

const int MASK = 1<<15;
const int inf = 1e9;
const int N = 15+5;

int n;
int m;
int len;
int v[N];
int deg[N];
int d[N][N];
int memo[MASK];
bool vis[MASK];

int DP(int mask){
	if(mask == 0) return 0;
	if(vis[mask]) return memo[mask];
	int ans = inf;
	int p1 = 31 - __builtin_clz(mask & (-mask));
	for(int m = mask ^ (1<<p1); m > 0; m &= m-1){
		int p2 = 31 - __builtin_clz((-m) & m);
		ans = min(ans, d[v[p1]][v[p2]] + DP(mask ^ (1<<p1) ^ (1<<p2)));
	}
	vis[mask] = true;
	return memo[mask] = ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			d[i][j] = i == j? 0 : inf;
		}
	}
	int suma = 0;
	for(int i=0; i<m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		suma += w;
		d[u][v] = min(d[u][v], w);
		d[v][u] = min(d[v][u], d[u][v]);
		deg[u] += 1;
		deg[v] += 1;
	}
	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				if(d[i][j] > d[i][k] + d[k][j]){
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(d[1][i] == inf and deg[i]){
			puts("-1");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++){
		if(deg[i] & 1){
			v[len++] = i;
		}
	}
	int ans = len == 0? suma : inf;
	int total = (1<<len) - 1;
	ans = min(ans, suma + DP(total));
	printf("%d\n", ans);
	return 0;
}
