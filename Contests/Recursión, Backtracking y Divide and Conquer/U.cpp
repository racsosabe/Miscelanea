#include<bits/stdc++.h>
using namespace::std;

int n, k, A, B;

long long solve(int L, int R, vector<int> &v){
	int len = R - L + 1;
	if(v.size() == 0) return A;
	long long ans = 1LL * B * v.size() * (R - L + 1);
	if(len % 2 == 0){
		vector<int> l;
		vector<int> r;
		int mi = (L + R) / 2;
		for(int i = 0; i < v.size(); i++){
			if(v[i] <= mi) l.emplace_back(v[i]);
			else r.emplace_back(v[i]);
		}
		ans = min(ans, solve(L, mi, l) + solve(mi+ 1 , R, r));
	}
	return ans;
}

int main(){
	scanf("%d %d %d %d", &n, &k, &A, &B);
	vector<int> v(k);
	for(int i = 0; i < k; i++){
		scanf("%d", &v[i]);
	}
	printf("%lld\n", solve(1, 1<<n, v));
	return 0;
}

