#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int p[N];
int id[N];
int cnt[N];
bool record[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", p+i);
	for(int i = 1; i <= n; i++){
		id[p[i]] = i;
	}
	set<int> S;
	int original = 0;
	for(int i = 1; i <= n; i++){
		if(S.empty() or (*S.rbegin()) < p[i]){
			record[i] = true;
			original += 1;
		}
		else{
			int val = *S.rbegin();
			S.erase(val);
			if(S.empty() or (*S.rbegin()) < p[i]) cnt[id[val]] += 1;
			S.emplace(val);
		}
		S.emplace(p[i]);
	}
	int res = n+1;
	int ans = 0;
	for(int i = 1; i <= n; i++){
		int cand = cnt[i] - record[i] + original;
		if(ans < cand){
			res = p[i];
			ans = cand;
		}
		else if(ans == cand) res = min(res, p[i]);
	}
	printf("%d\n", res);
	return 0;
}
