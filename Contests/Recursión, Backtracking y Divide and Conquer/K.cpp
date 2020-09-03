#include<bits/stdc++.h>
using namespace::std;

const int N = 10000 + 5;

int n;
int v[N];

void solve(int l, int r){
	if(l > r) return;
	if(l == r){
		printf("%d\n", v[l]);
		return;
	}
	int mi = l + 1;
	while(mi <= r and v[l] > v[mi]) mi += 1;
	solve(l + 1, mi - 1);
	solve(mi, r);
	printf("%d\n", v[l]);
}

int main(){
	while(scanf("%d", &v[n]) == 1){
		n += 1;
	}
	solve(0, n - 1);
	return 0;
}
