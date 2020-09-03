#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int m;
int len;
int a[N];
int b[N];
int val[N];
int nxtA[N][N];
int nxtB[N][N];
int memo[N][N];
bool vis[N][N];
vector<int> res;
int choice[N][N];

void compress(){
	set<int> S;
	for(int i = 1; i <= n; i++){
		S.emplace(a[i]);
	}
	for(int i = 1; i <= m; i++){
		S.emplace(b[i]);
	}
	S.emplace(2e9);
	map<int, int> id;
	for(int x : S){
		val[len] = x;
		id[x] = len++;
	}
	for(int i = 1; i <= n; i++){
		a[i] = id[a[i]];
	}
	for(int i = 1; i <= m; i++){
		b[i] = id[b[i]];
	}
	for(int i = 0; i < len; i++){
		nxtA[n + 1][i] = n + 1;
		nxtB[m + 1][i] = m + 1;
	}
	for(int i = n; i >= 1; i--){
		for(int j = 0; j < len; j++) nxtA[i][j] = nxtA[i + 1][j];
		nxtA[i][a[i]] = i;
	}
	for(int i = m; i >= 1; i--){
		for(int j = 0; j < len; j++) nxtB[i][j] = nxtB[i + 1][j];
		nxtB[i][b[i]] = i;
	}
}

int DP(int p1, int p2){
	if(p1 == n + 1 or p2 == m + 1) return 0;
	if(vis[p1][p2]) return memo[p1][p2];
	int ans = -1;
	for(int i = a[p1] + 1; i < len; i++){
		int nxtp1 = nxtA[p1 + 1][i];
		int nxtp2 = nxtB[p2 + 1][i];
		int cand = 1 + DP(nxtp1, nxtp2);
		if(ans < cand){
			ans = cand;
			choice[p1][p2] = i;
		}
	}
	vis[p1][p2] = true;
	return memo[p1][p2] = ans;
}

void rebuild(int p1, int p2){
	if(p1 == n + 1 or p2 == m + 1) return;
	res.emplace_back(val[a[p1]]);
	int nxt = choice[p1][p2];
	rebuild(nxtA[p1 + 1][nxt], nxtB[p2 + 1][nxt]);
}

int solve(){
	int ans = 0;
	int x = n + 1, y = m + 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i] == b[j]){
				int cand = DP(i, j);
				if(ans < cand){
					ans = cand;
					x = i;
					y = j;
				}
			}
		}
	}
	rebuild(x, y);
	return ans;
}

int main(){
	a[0] = -1;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
	compress();
	int ans = solve();
	printf("%d\n", ans);
	for(int i = 0; i < res.size(); i++){
		printf("%d%c", res[i], " \n"[i + 1 == res.size()]);
	}
	return 0;
}
