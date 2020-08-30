#include<bits/stdc++.h>
using namespace::std;

const int N = 50+5;
const int L = 100+5;


int n, m;
char s[L];
char a[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int sx, sy, tx, ty;

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < m and a[i][j] != '#';
}

bool solve(vector<int> &p){
	int x = sx;
	int y = sy;
	for(int i = 0; s[i]; i++){
		int dir = p[s[i] - '0'];
		x += dx[dir];
		y += dy[dir];
		if(!validPos(x, y)) return false;
		if(x == tx and y == ty) return true;
	}
	return false;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++){
		scanf("%s", a[i]);
		for(int j = 0; j < m; j++){
			if(a[i][j] == 'S'){
				sx = i;
				sy = j;
			}
			if(a[i][j] == 'E'){
				tx = i;
				ty = j;
			}
		}
	}
	scanf("%s", s);
	int ans = 0;
	vector<int> p(4);
	iota(p.begin(), p.end(), 0);
	do{
		ans += solve(p);
	}while(next_permutation(p.begin(), p.end()));
	printf("%d\n", ans);
	return 0;
}
