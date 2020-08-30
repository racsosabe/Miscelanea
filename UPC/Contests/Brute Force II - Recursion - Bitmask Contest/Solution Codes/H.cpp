#include<bits/stdc++.h>
using namespace::std;

int n;

bool almost(int x){
	int cnt = 0;
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0){
			while(x % i == 0) x /= i;
			cnt += 1;
		}
		if(cnt > 2) return false;
	}
	if(x > 1) cnt += 1;
	return cnt == 2;
}

int main(){
	scanf("%d", &n);
	int ans = 0;
	for(int i = 1; i <= n; i++){
		ans += almost(i);
	}
	printf("%d\n", ans);
	return 0;
}
