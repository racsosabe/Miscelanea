#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
	scanf("%d", &n);
	int ans = 0;
	for(int a = 0; a * 1234567 <= n; a++){
		for(int b = 0; a * 1234567 + b * 123456 <= n; b++){
			int left = n - a * 1234567 - b * 123456;
			if(left % 1234) continue;
			if(left >= 0){
				ans++;
			}
		}
	}
	puts(ans?"YES":"NO");
	return 0;
}

