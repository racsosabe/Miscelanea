#include<bits/stdc++.h>
using namespace::std;

const int N = 20 + 5;
const int inf = 1e9;

int n;
char s[N][N];
int dx[] = {1, -1, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0};

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < n;
}

int solve(int mask, int target){
	vector< vector<int> > v(n, vector<int>(n, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			v[i][j] = s[i][j] == 'b';
		}
	}
	for(int j = 0; j < n; j++){
		if((mask >> j) & 1){
			for(int k = 0; k < 5; k++){
				int vx = dx[k];
				int vy = j + dy[k];
				if(validPos(vx, vy)){
					v[vx][vy] ^= 1;
				}
			}
		}
	}
	int res = __builtin_popcount(mask);
	for(int i = 1; i < n; i++){
		for(int j = 0; j < n; j++){
			if(v[i-1][j] ^ target){
				res += 1;
				for(int k = 0; k < 5; k++){
					int vx = i + dx[k];
					int vy = j + dy[k];
					if(validPos(vx, vy)){
						v[vx][vy] ^= 1;
					}
				}
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(v[i][j] ^ target) return inf;
		}
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", s[i]);
	}
	int ans = inf;
	for(int mask = 0; mask < 1<<n; mask++){
		ans = min(ans, solve(mask, 0));
		ans = min(ans, solve(mask, 1));
	}
	if(ans == inf) puts("Impossible");
	else printf("%d\n", ans);
	return 0;
}

