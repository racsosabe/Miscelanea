#include<bits/stdc++.h>
using namespace::std;

const int N = 10;
const int M = 300;

int n, k;
int len[N];
char ans[M][M];
char table[N][N];

void solve(int x, int y, int depth, bool black){
	if(black){
		int L = len[depth + 1];
		for(int i = 0; i < L; i++){
			for(int j = 0; j < L; j++){
				ans[x + i][y + j] = '*';
			}
		}
		return;
	}
	if(depth == 0){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				ans[x + i][y + j] = table[i][j];
			}
		}
		return;
	}
	int dL = len[depth];
	int L = len[depth + 1];
	for(int i = 0; i < L; i += dL){
		for(int j = 0; j < L; j += dL){
			if(table[i / dL][j / dL] == '.'){
				solve(x + i, y + j, depth - 1, false);
			}
			else solve(x + i, y + j, depth - 1, true);
		}
	}
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%s", table[i]);
	}
	len[0] = 1;
	for(int i = 1; i <= k; i++) len[i] = n * len[i-1];
	memset(ans, '.', sizeof ans);
	solve(0, 0, k - 1, false);
	for(int i = 0; i < len[k]; i++){
		for(int j = 0; j < len[k]; j++){
			putchar(ans[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
