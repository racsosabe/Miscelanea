#include<bits/stdc++.h>
using namespace::std;

int n, m;
int ans = 0;
int len1, len2;

int getLen(int x){
	if(x < 7) return 1;
	return 1 + getLen(x / 7);
}

bool can(int x, int y){
	vector<int> A(len1, 0), B(len2, 0);
	int p = 0;
	while(x > 0){
		int d = x % 7;
		A[p++] = d;
		x /= 7;
	}
	p = 0;
	while(y > 0){
		int d = y % 7;
		B[p++] = d;
		y /= 7;
	}
	int mask = 0;
	for(int a : A){
		if(mask & (1<<a)) return false;
		mask |= 1<<a;
	}
	for(int a : B){
		if(mask & (1<<a)) return false;
		mask |= 1<<a;
	}
	return true;
}

int main(){
	scanf("%d %d", &n, &m);
	len1 = getLen(n-1);
	len2 = getLen(m-1);
	if(len1 + len2 <= 7){
		for(int a = 0; a < n; a++){
			for(int b = 0; b < m; b++){ 
				if(can(a, b)) ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
