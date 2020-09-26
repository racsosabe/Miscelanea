#include<bits/stdc++.h>
using namespace::std;

int n;
map<int, int> F;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		F[x] += 1;
	}
	int ans = 0;
	for(auto x : F){
		ans = max(ans, x.second);
	}
	printf("%d\n", ans);
	return 0;
}
