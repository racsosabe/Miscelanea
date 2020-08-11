#include<bits/stdc++.h>
using namespace::std;

const int N = 50000+5;
const int MOD = 1000000000+7;

int n;
int q;
int len[2];
int a[N][2][2];
int st1[2][N][2][2]; // 0 -> normal, 1 -> total
int st2[2][N][2][2]; // 0 -> normal, 1 -> total

inline int mul(int a, int b){
	return (1LL * a * b) % MOD;
}

void insert(int pos){
	len[0]++;
	for(int r = 0; r < 2; r++){
		for(int c = 0; c < 2; c++){
			st1[0][len[0]][r][c] = a[pos][r][c];
			st1[1][len[0]][r][c] = 0;
			for(int k = 0; k < 2; k++){
				st1[1][len[0]][r][c] += mul(st1[1][len[0]-1][r][k], a[pos][k][c]);
			}
			if(st1[1][len[0]][r][c] >= MOD) st1[1][len[0]][r][c] %= MOD;
		}
	}
}

void remove(){
	if(!len[1]){
		for(int j = len[0]; j >= 1; j--){
			len[1]++;
			for(int r = 0; r < 2; r++){
				for(int c = 0; c < 2; c++){
					st2[0][len[1]][r][c] = st1[0][j][r][c];
					st2[1][len[1]][r][c] = 0;
					for(int k = 0; k < 2; k++){
						st2[1][len[1]][r][c] += mul(st1[0][j][r][k], st2[1][len[1]-1][k][c]);
					}
					if(st2[1][len[1]][r][c] >= MOD) st2[1][len[1]][r][c] %= MOD;
				}
			}
		}
		len[0] = 0;
	}
	len[1] -= 1;
}

inline int trace(){
	int ans = 0;
	for(int i = 0; i < 2; i++){
		int j = i;
		for(int k = 0; k < 2; k++){
			ans += mul(st2[1][len[1]][i][k], st1[1][len[0]][k][j]);
			if(ans >= MOD) ans %= MOD;
		}
	}
	return ans;
}

int solve(int l){
	len[0] = 0;
	len[1] = 0;
	for(int i = 1; i < l; i++){
		insert(i);
	}
	int ans = 0;
	for(int i = max(1, l); i <= n; i++){
		insert(i);
		if(i - l >= 1) remove();
		ans = max(ans, trace());
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++){
		for(int r = 0; r < 2; r++){
			for(int c = 0; c < 2; c++){
				scanf("%d", &a[i][r][c]);
			}
		}
	}
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			st1[0][0][i][j] = st1[1][0][i][j] = st2[0][0][i][j] = st2[1][0][i][j] = i == j;
		}
	}
	for(int i = 1; i <= q; i++){
		int l;
		scanf("%d", &l);
		printf("%d\n", solve(l));
	}
	return 0;
}
