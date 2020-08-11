#include<bits/stdc++.h>
using namespace::std;

const int N = 1000+5;

int n, k;
int a[N];
int b[N];

bool can(int x){
	int needed = 0;
	for(int i = 1; i <= n; i++){
		needed += max(0, x * a[i] - b[i]);
	}
	return needed <= k;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	for(int i = 1; i <= n; i++){
		scanf("%d", b + i);
	}
	int ans = 0;
	while(can(ans + 1)) ans += 1;
	printf("%d\n",ans);
	return 0;
}
