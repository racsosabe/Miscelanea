#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];
long long ac[N];

bool solvePrefix(){
	for(int i = 1; i <= n; i++) ac[i] = ac[i - 1] + a[i];
	set<long long> S;
	long long wanted = ac[n] / 2;
	for(int i = 1; i < n; i++){
		S.emplace(a[i]);
		if(ac[i] == wanted) return true;
		if(S.count(ac[i + 1] - wanted)) return true;
	}
	return false;
}


int main(){
	scanf("%d", &n);
	long long S = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		S += a[i];
	}
	if(S & 1){
		puts("NO");
		return 0;
	}
	bool can = solvePrefix();
	reverse(a + 1, a + n + 1);
	can |= solvePrefix();
	puts(can? "YES" : "NO");
	return 0;	
}
