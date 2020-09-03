#include<bits/stdc++.h>
using namespace::std;

int n;
vector<int> v;

long long merge(vector<int> &L, vector<int> &R){
	long long ans = 0LL;
	int posR = 0;
	for(int i = 0; i < L.size(); i++){
		while(posR < R.size() and R[posR] <= L[i]){
			posR += 1;
		}
		ans += 1LL * posR * L[i];
	}
	int posL = 0;
	for(int i = 0; i < R.size(); i++){
		while(posL < L.size() and L[posL] < R[i]){
			posL += 1;
		}
		ans += 1LL * posL * R[i];
	}
	return ans;
}

long long solve(vector<int> &v){
	if(v.size() == 1) return v[0];
	int len = v.size() / 2;
	vector<int> L(v.begin(), v.begin() + len);
	vector<int> R(v.begin() + len, v.end());
	long long ans = solve(L) + solve(R);
	reverse(L.begin(), L.end());
	for(int i = 1; i < L.size(); i++){
		L[i] = max(L[i-1], L[i]);
	}
	for(int i = 1; i < R.size(); i++){
		R[i] = max(R[i-1], R[i]);
	}
	ans += merge(L, R);
	return ans;
}

int main(){
	scanf("%d", &n);
	v.resize(n);
	for(int i = 0; i < n; i++) scanf("%d", &v[i]);
	long long ans = solve(v);
	for(int i = 0; i < n; i++) v[i] = -v[i];
	ans += solve(v);
	printf("%lld\n",ans);
	return 0;
}
