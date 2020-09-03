#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
	while(scanf("%d", &n) == 1 and n){
		int a = 0;
		int b = 0;
		int cnt = 0;
		for(int i = 0; i < 31; i++){
			if((n >> i) & 1){
				if(cnt){
					b |= 1<<i;
				}
				else{
					a |= 1<<i;
				}
				cnt ^= 1;
			}
		}
		printf("%d %d\n", a, b);
	}
	return 0;
}
