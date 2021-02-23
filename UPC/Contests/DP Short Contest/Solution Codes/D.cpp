#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int inf = 1e9;
const string moves = "DR";

int n;
int a[N][N];
int v[N][N];
int p[N][N];
int memo[N][N];
int dx[] = {-1, 0};
int dy[] = {0, -1};

pair<int, string> solve(int f){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(a[i][j] == 0) v[i][j] = inf;
			else{
				int e = 0;
				while(a[i][j] % f == 0){
					e += 1;
					a[i][j] /= f;
				}
				v[i][j] = e;
			}
		}
	}
	memo[1][1] = v[1][1];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i + j == 2) continue;
			memo[i][j] = inf;
			if(i - 1 >= 1 and v[i][j] + memo[i - 1][j] < memo[i][j]){
				memo[i][j] = v[i][j] + memo[i - 1][j];
				p[i][j] = 0;
			}
			if(j - 1 >= 1 and v[i][j] + memo[i][j - 1] < memo[i][j]){
				memo[i][j] = v[i][j] + memo[i][j - 1];
				p[i][j] = 1;
			}
		}
	}
	string res = "";
	int x = n, y = n;
	for(int i = 0; i < 2 * (n - 1); i++){
		int dir = p[x][y];
		res += moves[dir];
		x += dx[dir];
		y += dy[dir];
	}
	reverse(res.begin(), res.end());
	return make_pair(memo[n][n], res);
}

int main(){
	scanf("%d", &n);
	int x = 0, y = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &a[i][j]);
			if(a[i][j] == 0){
				x = i;
				y = j;
			}
		}
	}
	int ans = inf;
	string res = "";
	if(x >= 1){
		ans = 1;
		for(int i = 1; i < x; i++){
			res += 'D';
		}
		for(int i = 1; i < n; i++){
			res += 'R';
		}
		for(int i = x; i < n; i++){
			res += 'D';
		}
	}
	pair<int, string> res2 = solve(2), res5 = solve(5);
	if(res2.first < ans){
		ans = res2.first;
		res = res2.second;
	}
	if(res5.first < ans){
		ans = res5.first;
		res = res5.second;
	}
	printf("%d\n%s\n", ans, res.c_str());
	return 0;
}
