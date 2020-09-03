#include<bits/stdc++.h>
using namespace::std;

const int N = 20+5;

int n,m;
long long k;
long long v[N][N];
map<long long, int> values1[N][N];
map<long long, int> values2[N][N];

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < m;
}

void backtracking(int x, int y, long long current, int dx, int dy){
	if(x + y == n-1){
		if(dx > 0) values1[x][y][current ^ v[x][y]]++;
		else values2[x][y][current]++;
		return;
	}
	if(validPos(x + dx, y)){
		backtracking(x + dx, y, current ^ v[x][y], dx, dy);
	}
	if(validPos(x, y + dy)){
		backtracking(x, y + dy, current ^ v[x][y], dx, dy);
	}	
}

int main(){
	scanf("%d %d %lld", &n, &m, &k);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%lld", &v[i][j]);
		}
	}
	backtracking(0, 0, 0, 1, 1);
	backtracking(n - 1, m - 1, 0, -1, -1);
	long long ans = 0;
	for(int i = 0; i < n; i++){
		for(auto x : values1[i][n - 1 - i]){
			long long needed = k ^ x.first;
			ans += 1LL * x.second * values2[i][n-1-i][needed];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
