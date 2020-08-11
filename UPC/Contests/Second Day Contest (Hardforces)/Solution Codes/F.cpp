#include<bits/stdc++.h>
using namespace::std;

const int N = 30+5;

int n;
int t[N];
set< pair<int, int> > S;
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
set< pair< pair<int, int>, pair<int, int> > > memo;

void backtracking(int x, int y, int depth, int dir){
	if(memo.count(make_pair(make_pair(x, y), make_pair(depth, dir)))) return;
	memo.emplace(make_pair(make_pair(x, y), make_pair(depth, dir)));
	for(int i = 0; i < t[depth]; i++){
		S.emplace(make_pair(x, y));
		x += dx[dir];
		y += dy[dir];
	}
	x -= dx[dir];
	y -= dy[dir];
	if(depth == n) return;
	int pdir = dir > 0? dir - 1 : dir - 1 + 8;
	int ndir = dir + 1 < 8? dir + 1 : dir + 1 - 8;
	backtracking(x + dx[pdir], y + dy[pdir], depth + 1, pdir);
	backtracking(x + dx[ndir], y + dy[ndir], depth + 1, ndir);
}

int solve(){
	backtracking(0, 0, 1, 0);
	return S.size();
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", t + i);
	}
	printf("%d\n", solve());
	return 0;
}
