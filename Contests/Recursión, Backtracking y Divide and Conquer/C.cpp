#include<bits/stdc++.h>
using namespace::std;

int n;

int f(int x){
	if(x <= 101) return 91;
	return x - 10;
}

int main(){
	while(scanf("%d", &n) == 1 and n > 0){
		printf("f91(%d) = %d\n", n, f(n));
	}	
	return 0;
}
