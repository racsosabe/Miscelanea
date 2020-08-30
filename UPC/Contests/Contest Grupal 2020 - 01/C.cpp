#include<bits/stdc++.h>
using namespace::std;

const int N = 2000+5;

int n;
int m;
char s[N];

void read(){
	n = 0;
	char c = getchar();
	while(c != '\n'){
		s[n++] = c;
		c = getchar();
	}
}

int main(){
	scanf("%d\n", &n);
	read();
	scanf("%d", &m);
	stack<char> S;
	char op[10];
	bool lowercase = true;
	for(int i = 0; i < m; i++){
		scanf("%s", op);
		if(op[0] == 'C'){
			lowercase = !lowercase;
		}
		else if(op[0] == 'B'){
			if(!S.empty()) S.pop();
		}
		else if(op[0] == 'S'){
			S.emplace(' ');
		}
		else{
			char res = lowercase? op[0] : op[0] + 'A' - 'a';
			S.emplace(res);
		}
	}
	if(S.size() != n) puts("Incorrect");
	else{
		while(!S.empty()){
			if(S.top() != s[n - 1]){
				puts("Incorrect");
				return 0;
			}
			n -= 1;
			S.pop();
		}
		puts("Correct");
	}
	return 0;
}
