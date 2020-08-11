#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
	scanf("%d", &n);
	int ans = 0;
	for(int a = 1; a <= n; a++){
		for(int b = a; b <= n; b++){
			int c = (a^b);
			if(c < max(a,b)) continue;
			if(c < 1 or c > n) continue;
			if(c >= a+b) continue;
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}

