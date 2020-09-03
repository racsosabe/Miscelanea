#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

char s[N];

int degree(int x){
	if(x == 9) return 0;
	int sum = 0;
	while(x > 0){
		sum += x % 10;
		x /= 10;
	}
	return 1 + degree(sum);
}

int main(){
	while(scanf("%s", s) == 1){
		int sum = 0;
		for(int i = 0; s[i]; i++){
			sum += s[i] - '0';
		}
		if(sum == 0) break;
		if(sum % 9) printf("%s is not a multiple of 9.\n", s);
		else printf("%s is a multiple of 9 and has 9-degree %d.\n", s, degree(sum) + 1);
	}
	return 0;
}
