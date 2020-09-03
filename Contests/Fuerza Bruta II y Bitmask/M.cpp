#include<bits/stdc++.h>
using namespace::std;

int n;
int ans;

void backtracking(int x, int y, long long val){
	if(val > n) return;
	if(val > 0) ans += 1;
	if(y == -1){
		backtracking(x, y, 10 * val + x);
		for(int i = 0; i < 10; i++){
			if(i == x) continue;
			backtracking(x, i, 10 * val + i);
		}
	}
	else{
		backtracking(x, y, 10 * val + x);
		backtracking(x, y, 10 * val + y);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < 10; i++){
		backtracking(i, -1, i);
	}
	printf("%d\n", ans);
	return 0;
}
