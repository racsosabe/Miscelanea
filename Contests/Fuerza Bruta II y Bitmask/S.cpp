#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;
const int LOG = 62;

int n;
bool vis[N];
long long v[N];
vector<long long> ans;
vector<long long> sets[LOG];

int getOrder(long long x){
	return 63 - __builtin_clzll(x);
}

void solve(){
	for(int i =0 ; i < n; i++){
		sets[getOrder(v[i] & (-v[i]))].emplace_back(v[i]);
	}
	int best = 0;
	for(int i = 0; i < LOG; i++){
		if(sets[best].size() < sets[i].size()) best = i;
	}
	for(int i = 0; i < LOG; i++){
		if(i == best) continue;
		for(auto x : sets[i]) ans.emplace_back(x);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%lld", &v[i]);
	}
	solve();
	printf("%d\n", (int)ans.size());
	for(int i = 0; i < ans.size(); i++){
		printf("%lld%c",ans[i]," \n"[i + 1 == ans.size()]);
	}
	return 0;
}
