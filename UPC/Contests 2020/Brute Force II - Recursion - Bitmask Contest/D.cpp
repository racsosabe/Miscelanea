#include<bits/stdc++.h>
using namespace::std;

int n;
int mask;
int shocks;
int total = (1<<26) - 1;

void process(){
	char c = getchar();
	while(c != '!' and c != '.' and c != '?'){
		c = getchar();
	}
	if(c == '!'){
		shocks += 1;
		c = getchar();
		while(!isalpha(c)) c = getchar();
		int cur = 0;
		while(isalpha(c)){
			cur |= 1<<(c - 'a');
			c = getchar();
		}
		mask &= cur;
	}
	else if(c == '.'){
		c = getchar();
		while(!isalpha(c)) c = getchar();
		int cur = 0;
		while(isalpha(c)){
			cur |= 1<<(c - 'a');
			c = getchar();
		}
		mask &= (total^cur);
	}
	else{
		shocks += 1;
		c = getchar();
		while(!isalpha(c)) c = getchar();
		int cur = 0;
		while(isalpha(c)){
			cur |= 1<<(c - 'a');
			c = getchar();
		}
		mask &= (total^cur);
	}
}

int main(){
	scanf("%d", &n);
	mask = (1<<26)-1;
	int stopped = -1;
	for(int i = 1; i <= n; i++){
		process();
		if(__builtin_popcount(mask) <= 1 and stopped == -1){
			stopped = shocks;
		}
	}
	if(__builtin_popcount(mask) <= 1) printf("%d\n", shocks - 1 - stopped);
	else puts("0");
	return 0;
}
