#include<bits/stdc++.h>
using namespace::std;

const int M = 1100000;
const int N = 100000+5;
const int LOG = 20;

int n;
int ans;
bool vis[M];
int ac[N][LOG];

int getValue(int L, int R){
	int ans = 0;
	for(int i = 0; i < LOG; i++){
		ans += (1 << i) * (ac[R][i] > ac[L-1][i]);
	}
	return ans;
}

void markValues(int L){
	int R = L;
	while(R <= n){
		int val = getValue(L,R);
		if(!vis[val]) ans += 1;
		vis[val] = true;
		int nxtR = n;
		while(R < nxtR){
			int mi = R + (nxtR - R + 1) / 2;
			if(getValue(L,mi) == val) R = mi;
			else nxtR = mi - 1;
		}
		R = nxtR + 1;
	}
}

int main(){
	scanf("%d", &n);
	int x;
	for(int i = 1; i <= n; i++){
		scanf("%d", &x);
		for(int j = 0; j < LOG; j++){
			ac[i][j] = (x >> j) & 1;
			ac[i][j] += ac[i-1][j];
		}
	}
	for(int i = 1; i <= n; i++){
		markValues(i);
	}
	printf("%d\n", ans);
	return 0;
}

