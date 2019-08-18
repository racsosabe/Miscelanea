#include<bits/stdc++.h>
using namespace::std;

/*
	Problem: Petya and Array - Codeforces 1042D

	Author: Racso Galvan
*/

int n;
long long t;

long long merge(vector<long long> &L, vector<long long> &R){
	int pR = R.size() - 1;
	long long ans = 0LL;
	for(int i=0; i<L.size(); i++){
		while(pR >= 0 and L[i] + R[pR] >= t){
			pR -= 1;
		}
		ans += pR + 1;
	}
	vector< pair<long long,int> > F;
	int l = 0, r = 0;
	while(l < R.size()){
		while(r < R.size() and R[l] == R[r]){
			r++;
		}
		F.emplace_back(make_pair(R[l],r-l));
		l = r;
	}
	pR = F.size() - 1;
	for(int i=0; i<L.size(); i++){
		while(pR >= 0 and L[i] + F[pR].first > t){
			pR -= 1;
		}
		if(pR >= 0 and L[i] + F[pR].first == t){
			ans += F[pR].second;
		}
	}
	return ans;
}

void computePrefix(vector<long long> &v){
	for(int i=1; i<v.size(); i++){
		v[i] += v[i-1];
	}
}

long long solve(vector<long long> &v){
	int len = v.size();
	if(len <= 1){
		return v[0] <= t;
	}
	vector<long long> L(v.begin(), v.begin() + len/2);
	vector<long long> R(v.begin() + len/2, v.end());
	long long ans = 0LL;
	ans += solve(L);
	ans += solve(R);
	computePrefix(R);
	reverse(L.begin(),L.end());
	computePrefix(L);
	sort(R.begin(),R.end());
	sort(L.begin(),L.end());
	ans += merge(L,R);
	return ans;
}

int main(){
	scanf("%d %lld",&n,&t);
	t -= 1;
	vector<long long> v(n);
	for(int i=0; i<n; i++){
		scanf("%lld",&v[i]);
	}
	long long ans = solve(v);
	cout << ans << endl;
	return 0;
}
