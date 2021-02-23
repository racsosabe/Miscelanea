#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
char s[N];
int memo[N];

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	stack<int> S;
	for(int i = 1; i <= n; i++){
		if(s[i] == ')'){
			if(!S.empty()){
				int x = S.top();
				memo[i] = memo[x - 1] + i - x + 1;
				S.pop();
			}
		}
		else{
			S.emplace(i);
		}
	}
	int res = *max_element(memo + 1, memo + n + 1);
	int cnt = 0;
	if(res > 0) for(int i = 1; i <= n; i++) cnt += memo[i] == res;
	else cnt = 1;
	printf("%d %d\n", res, cnt);
	return 0;
}
