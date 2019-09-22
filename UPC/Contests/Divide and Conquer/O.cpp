#include<bits/stdc++.h>
using namespace::std;

/*
	Problem: Points on Line - Codeforces 251A

	Author: Racso Galvan
*/

int n, d;

int getLen(int L, vector<int> &v){
	int lo = L, hi = n-1;
	while(lo < hi){
		int mi = lo + (hi-lo+1)/2;
		if(v[mi] - v[L] <= d) lo = mi;
		else hi = mi-1;
	}
	return lo - L + 1;
}

long long getPairs(long long x){
	return x * (x-1) / 2LL;
}

long long solve(vector<int> &v){
	long long ans = 0LL;
	for(int i=0; i<n; i++){
		ans += getPairs(getLen(i,v)-1);
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&d);
	vector<int> v(n);
	for(int i=0; i<n; i++){
		scanf("%d",&v[i]);
	}
	long long ans = solve(v);
	cout << ans << endl;
	return 0;
}
