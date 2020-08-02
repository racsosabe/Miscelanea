#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;

int n;
char s[N];
int par[N];
int sizes[N];

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
}

vector<int> build(int s1, int s2){
	vector<int> ans;
	for(int i = s1 - 1; i >= 0; i--){
		if(s[i] == '.'){
			ans.emplace_back(i);
			break;
		}
	}
	for(int i = s1 + 1; i < n; i++){
		if(s[i] == '.'){
			ans.emplace_back(i);
			break;
		}
	}
	for(int i = s2 - 1; i >= 0; i--){
		if(s[i] == '.'){
			ans.emplace_back(i);
			break;
		}
	}
	for(int i = s2 + 1; i < n; i++){
		if(s[i] == '.'){
			ans.emplace_back(i);
			break;
		}
	}
	return ans;
}

bool reachable(int start, int t){
	for(int i = 0; i < n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	int last_portal = -1;
	for(int i = 0; i < n; i++){
		if(s[i] == '#') continue;
		if(s[i] != 'o'){
			if(i - 1 >= 0 and s[i - 1] != '#') join(i - 1, i);
			if(i + 1 < n and s[i + 1] != '#') join(i + 1, i);
		}
		if(s[i] == 'o'){
			if(last_portal >= 0) join(last_portal, i);
			last_portal = i;
		}
	}
	return get(start) == get(t);
}

int test(int mask, vector<int> &v, int start, int t){
	for(int i = 0; i < v.size(); i++){
		if((mask >> i) & 1){
			s[v[i]] = '#';
		}
	}
	int ans = reachable(start, t)? -1 : __builtin_popcount(mask);
	for(int i = 0; i < v.size(); i++){
		if((mask >> i) & 1){
			s[v[i]] = '.';
		}
	}
	return ans;
}

int solve(){
	int start, goal;
	for(int i = 0; i < n; i++){
		if(s[i] == 's') start = i;
		if(s[i] == 'e') goal = i;
	}
	vector<int> v = build(start, goal);
	int len = v.size();
	int res = -1;
	for(int mask = 0; mask < 1<<len; mask++){
		int cand = test(mask, v, start, goal);
		if(cand != -1){
			if(res == -1 or res > cand) res = cand;
		}
	}
	return res;
}

int main(){
	freopen("portals.in", "r", stdin);
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		scanf("%s", s);
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}
