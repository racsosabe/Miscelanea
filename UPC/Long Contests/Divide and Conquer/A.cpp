#include<bits/stdc++.h>
using namespace::std;

/*
	Problem: Imbalanced Array - Codeforces 817D

	Author: Racso Galvan

*/

int n;

long long merge(vector<int> &L, vector<int> &R){
	int pR = 0;
	long long ans = 0LL;
	for(int i=0; i<L.size(); i++){
		while(pR < R.size() and R[pR] <= L[i]){
			pR += 1;
		}
		ans += 1LL * L[i] * pR;
	}
	int pL = 0;
	for(int i=0; i<R.size(); i++){
		while(pL < L.size() and L[pL] < R[i]){
			pL += 1;
		}
		ans += 1LL * R[i] * pL;
	}
	return ans;
}

void getMax(vector<int> &v){
	for(int i=1; i<v.size(); i++){
		v[i] = max(v[i],v[i-1]);
	}
}

long long solve(vector<int> &v){
	int len = v.size();
	if(len <= 1){
		return v[0];
	}
	vector<int> L(v.begin(),v.begin() + len/2);
	vector<int> R(v.begin() + len/2, v.end());
	long long ans = 0LL;
	ans += solve(L);
	ans += solve(R);
	reverse(L.begin(),L.end());
	getMax(L);
	getMax(R);
	ans += merge(L,R);
	return ans;
}

int main(){
	scanf("%d",&n);
	vector<int> v(n);
	for(int i=0; i<n; i++){
		scanf("%d",&v[i]);
	}
	long long ans = solve(v);
	for(int i=0; i<n; i++){
		v[i] = -v[i];
	}
	ans += solve(v);
	cout << ans << endl;
	return 0;	
}
