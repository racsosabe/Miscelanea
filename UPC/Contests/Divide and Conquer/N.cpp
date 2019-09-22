#include<bits/stdc++.h>
using namespace::std;

/*
	Problem: Three Sorted Arrays - Codeforces Gym 100589J

	Author: Racso Galvan
*/

const int N = 100000+5;

int n[3];
int a[3][N];
long long F[3][N];

void solve(int L, int R){
	for(int i=n[R]-1; i>=0; i--){
		F[R][i] += F[R][i+1];
	}
	for(int i=0; i<n[L]; i++){
		int lo = min(i,n[R]), hi = n[R];
		while(lo < hi){
			int mi = lo + (hi-lo)/2;
			if(a[R][mi] < a[L][i]) lo = mi+1;
			else hi = mi;
		}
		F[L][i] += F[R][lo];
	}
}

void clearAll(){
	for(int i=0; i<3; i++){
		for(int j=0; j<=n[i]; j++){
			F[i][j] = 0LL;
		}
	}
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		for(int i=0; i<3; i++){
			scanf("%d",n+i);
			for(int j=0; j<n[i]; j++){
				F[i][j] = 0LL;
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=0; i<n[2]; i++) F[2][i] = 1;
		solve(1,2);
		solve(0,1);
		long long ans = 0LL;
		for(int i=0; i<n[0]; i++){
			ans += F[0][i];
		}
		cout << ans << endl;
		if(t) clearAll();
	}
	return 0;
}
