#include<bits/stdc++.h>
using namespace::std;

int n;
int a = 1, b = 2, c = 3;

int main(){
	scanf("%d", &n);
	int winner;
	bool can = true;
	for(int i = 1; i <= n; i++){
		scanf("%d", &winner);
		if(winner == c){
			can = false;
		}
		int loser = a ^ b ^ winner;
		if(b == winner) swap(a, b);
		swap(b, c);
		c = loser;
	}
	puts(can? "YES" : "NO");
	return 0;
}

