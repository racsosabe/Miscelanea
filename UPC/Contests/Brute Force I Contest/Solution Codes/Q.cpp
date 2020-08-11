#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;

int n, m;
char table[N][N];

int main(){
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++){
		scanf("%s", table[i]);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(table[i][j] == '-') continue;
			table[i][j] = (i+j)&1?'W':'B';
		}
	}
	for(int i=0; i<n; i++){
		printf("%s\n", table[i]);
	}
	return 0;
}

