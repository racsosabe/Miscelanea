#include<bits/stdc++.h>
using namespace::std;

int l, r;
vector<long long> lucky;

long long solve(long long x){
	if(x == 0) return 0LL;
	long long res = 0;
	long long last = 0;
	for(auto a : lucky){
		long long r = min(a, x);
		res += (r - last) * a;
		last = r;
	}
	return res;
}

void backtracking(long long val){
	if(val > 1e10) return;
	lucky.emplace_back(val);
	backtracking(10 * val + 4);
	backtracking(10 * val + 7);
}

int main(){
	backtracking(4);
	backtracking(7);
	sort(lucky.begin(), lucky.end());
	scanf("%d %d", &l, &r);
	printf("%lld\n", solve(r) - solve(l - 1));
	return 0;
}
