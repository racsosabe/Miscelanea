#include<bits/stdc++.h>
using namespace::std;

int k;

bool perfect(int x){
	int suma = 0;
	while(x > 0){
		suma += x % 10;
		x /= 10;
	}
	return suma == 10;
}

int main(){
	scanf("%d", &k);
	int ans = 19;
	k--;
	while(k > 0){
		ans += 9;
		if(perfect(ans)) k--;
	}
	printf("%d\n", ans);
	return 0;
}

