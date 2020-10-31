#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;
const int LOG = 20;

int n;
char s[N];
int pi[N];

bool can(int len){
	for(int i = len; i + 1 < n; i++){
		if(pi[i] >= len) return true;
	}
	return false;
}

int main(){
	scanf("%s", s);
	n = strlen(s);
	int k = 0;
	for(int i = 1; i < n; i++){
		while(k > 0 and s[k] != s[i]) k = pi[k - 1];
		if(s[k] == s[i]) k += 1;
		pi[i] = k;
	}
	int res = pi[n - 1];
	while(res > 0){
		if(can(res)){
			break;
		}
		res = pi[res - 1];
	}
	if(!res){
		puts("Just a legend");
		return 0;
	}
	for(int i = 0; i < res; i++){
		putchar(s[i]);
	}
	putchar('\n');
	return 0;
}
