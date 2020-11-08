#include<bits/stdc++.h>
using namespace::std;

int A, B, C;

bool check(int a, int b, int c){
	if(1LL * a * b * c != B) return false;
	return 1LL * a * a + 1LL * b * b + 1LL * c * c == C;
}

int main(){
	scanf("%d %d %d", &A, &B, &C);
	for(int a = -1000; a <= 1000; a++){
		for(int b = -1000; b <= 1000; b++){
			if(a == b) continue;
			int c = A - a - b;
			if(a == c or b == c) continue;
			if(check(a, b, c)){
				printf("%d %d %d\n", a, b, c);
				return 0;
			}
		}
	}
	puts("No solution.");
	return 0;
}
