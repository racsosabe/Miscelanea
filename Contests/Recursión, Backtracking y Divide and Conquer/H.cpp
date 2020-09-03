#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const int n = 8;

int len;
int a[N];
vector<int> v[N];

void backtracking(int pos, vector<int> &cur){
	if(pos == n){
		v[len++] = cur;
		return;
	}
	for(int y = 0; y < n; y++){
		bool valid = true;
		for(int i = 0; i < pos; i++){
			if(cur[i] == y) valid = false;
			if(pos - i == abs(y - cur[i])) valid = false;
		}
		if(valid){
			cur.emplace_back(y);
			backtracking(pos + 1, cur);
			cur.pop_back();
		}
	}
}

void init(){
	vector<int> cur;
	backtracking(0, cur);
}

int solve(){
	int ans = INT_MAX;
	for(int i = 0; i < len; i++){
		int act = 0;
		for(int j = 0; j < n; j++){
			act += (a[j] != v[i][j] + 1);
		}
		ans = min(ans, act);
	}
	return ans;
}

int main(){
	init();
	int caso = 1;
	while(scanf("%d", &a[0]) == 1){
		for(int i = 1; i < n; i++){
			scanf("%d", &a[i]);
		}
		printf("Case %d: %d\n", caso++, solve());
	}	
	return 0;
}
