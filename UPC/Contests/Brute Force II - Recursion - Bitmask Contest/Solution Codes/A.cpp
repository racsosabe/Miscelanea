#include<bits/stdc++.h>
using namespace::std;

const int N = 5000+5;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	map<int, int> F;
	for(int i = 1; i <= n; i++){
		F[a[i]] += 1;
	}
	int ans = 0;
	for(auto x : F){
		ans = max(ans, x.second);
	}
	printf("%d\n", ans);
	return 0;
}
