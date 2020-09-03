#include<bits/stdc++.h>
using namespace::std;

const int N = 21;

int n;
int C;
int w[N];
int ans = 1e9;

void backtracking(int pos, int sum){
	if(pos == n){
		ans = min(ans, C - 2 * sum);
		return;
	}
	backtracking(pos + 1, sum);
	if(sum + w[pos] <= C - sum - w[pos]) backtracking(pos + 1, sum + w[pos]);
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &w[i]);
	C = accumulate(w, w + n, 0);
	backtracking(0, 0);
	printf("%d\n", ans);
	return 0;
}
