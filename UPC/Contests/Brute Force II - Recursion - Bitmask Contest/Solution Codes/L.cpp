#include<bits/stdc++.h>
using namespace::std;

const int N = 10 + 5;

int n;
int ans;
char a[N];
char b[N];
int target;

void backtracking(int pos, int x){
	if(pos == n){
		ans += x == target;
		return;
	}
	if(b[pos] == '?'){
		backtracking(pos + 1, x + 1);
		backtracking(pos + 1, x - 1);
	}
	else{
		x += b[pos] == '+'? 1 : -1;
		backtracking(pos + 1, x);
	}
}

int main(){
	scanf("%s", a);
	scanf("%s", b);
	n = strlen(a);
	int total = 0;
	for(int i = 0; i < n; i++){
		if(a[i] == '+') target += 1;
		else target -= 1;
		if(b[i] == '?') total += 1;
	}
	total = 1<<total;
	backtracking(0, 0);
	printf("%.10lf\n", 1.0 * ans / total);
	return 0;
}
