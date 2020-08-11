#include<bits/stdc++.h>
using namespace::std;

const int inf = 2e9;
const int N = 11;

int n, k;
int v[N];
char s[N][N];

int main(){
	scanf("%d %d", &n, &k);
	for(int i=0; i<n; i++){
		scanf("%s", s[i]);
	}
	for(int i=0; i<k; i++){
		v[i] = i;
	}
	int ans = inf;
	do{
		int maximo = -1;
		int minimo = inf;
		for(int i=0; i<n; i++){
			int act = 0;
			for(int j=0; j<k; j++){
				int digit = s[i][v[j]] - '0';
				act = (act<<1) + (act<<3) + digit;
			}
			maximo = max(maximo,act);
			minimo = min(minimo,act);
		}
		ans = min(ans,maximo - minimo);
	}while(next_permutation(v, v + k));
	printf("%d\n", ans);
	return 0;
}

