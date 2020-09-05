#include<bits/stdc++.h>
using namespace::std;

const int N = 300+5;

int n;
bool vis[N][N][N];
long double memo[N][N][N];

long double DP(int unos, int dos, int tres){
	int total = unos + dos + tres;
	if(total == 0) return 0.0L;
	if(vis[unos][dos][tres]) return memo[unos][dos][tres];
	long double ans = 1.0 * n / total;
	if(unos > 0){
		ans += unos * DP(unos - 1, dos, tres) / total;
	}
	if(dos > 0){
		ans += dos * DP(unos + 1, dos - 1, tres) / total;
	}
	if(tres > 0){
		ans += tres * DP(unos, dos + 1, tres - 1) / total;
	}
	vis[unos][dos][tres] = true;
	return memo[unos][dos][tres] = ans;
}

int main(){
	scanf("%d", &n);
	int unos = 0, dos = 0, tres = 0;
	for(int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		if(x == 1) unos++;
		else if(x == 2) dos++;
		else tres++;
	}
	printf("%.10Lf\n", DP(unos, dos, tres));
	return 0;
}

