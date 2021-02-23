#include<bits/stdc++.h>
using namespace::std;

const int N = 5000 + 5;

int n;
int q;
char s[N];
bool pal[N][N];
int memo[N][N];

void preprocess(){
	for(int i = 1; i <= n; i++) pal[i][i] = memo[i][i] = 1;
	for(int i = 1; i + 1 <= n; i++) pal[i][i + 1] = s[i] == s[i + 1];
	for(int L = 3; L <= n; L++){
		for(int i = 1; i + L - 1 <= n; i++){
			int j = i + L - 1;
			pal[i][j] = pal[i + 1][j - 1] and (s[i] == s[j]);
		}
	}
	for(int L = 2; L <= n; L++){
		for(int i = 1; i + L - 1 <= n; i++){
			int j = i + L - 1;
			memo[i][j] = int(pal[i][j]) + memo[i + 1][j] + memo[i][j - 1] - memo[i + 1][j - 1];
		}
	}
}

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	preprocess();
	scanf("%d", &q);
	while(q--){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", memo[l][r]);
	}
	return 0;
}
