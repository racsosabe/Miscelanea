#include<bits/stdc++.h>
using namespace::std;

int mask(int x){
	int p = 1;
	int ans = 0;
	while(x > 0){
		if(x % 10 == 4 or x % 10 == 7){
			ans += p * (x % 10);
			p *= 10;
		}
		x /= 10;
	}
	return ans;
}

int main(){
	int a, b;
	scanf("%d %d", &a, &b);
	a++;
	while(mask(a) != b){
		a++;
	}
	printf("%d\n", a);
	return 0;
}

