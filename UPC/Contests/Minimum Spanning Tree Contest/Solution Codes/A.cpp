#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;
const int M = 400000+5;

int n, m;
int L[M];
int R[M];
int s, t;
int ds, dt;
int par[N];
int mask[N];
int sizes[N];

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

bool join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return false;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	return true;
}

void parse(vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &d, int &can){
	for(int i=1; i <= m; i++){
		if(R[i] == s) swap(L[i], R[i]);
		if(L[i] == t) swap(L[i], R[i]);
		if(L[i] == s and R[i] == t){
			can = i;
			continue;
		}
		if(L[i] == s){
			mask[R[i]] |= 1;
			continue;
		}
		if(R[i] == t){
			mask[L[i]] |= 2;
			continue;
		}
		d.emplace_back(i);
	}
	for(int i=1; i<=m; i++){
		if(L[i] == s and R[i] == t) continue;
		if(L[i] == s){
			if(mask[R[i]] == 1) a.emplace_back(i);
			else c.emplace_back(i);
		}
		if(R[i] == t){
			if(mask[L[i]] == 2) b.emplace_back(i);
			else c.emplace_back(i);
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++) scanf("%d %d", &L[i], &R[i]);
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	scanf("%d %d", &s, &t);
	scanf("%d %d", &ds, &dt);
	int joined = 0;
	vector<int> onlyS, onlyT, both, none;
	parse(onlyS, onlyT, both, none, joined);
	vector<int> ans;
	int comp = n;
	for(int i : none){
		if(join(L[i], R[i])){
			ans.emplace_back(i);
			comp -= 1;
		}
	}
	if(comp - 1 > ds + dt){
		puts("No");
		return 0;
	}
	for(int i : onlyS){
		if(ds > 0 and join(L[i], R[i])){
			ans.emplace_back(i);
			ds -= 1;
			comp -= 1;
		}
	}
	for(int i : onlyT){
		if(dt > 0 and join(L[i], R[i])){
			ans.emplace_back(i);
			dt -= 1;
			comp -= 1;
		}
	}
	for(int i : both){
		if(ds > 0 and L[i] == s){
			if(join(L[i], R[i])){
				ans.emplace_back(i);
				ds -= 1;
				comp -= 1;
			}
		}
		else if(dt > 0 and R[i] == t){
			if(join(L[i], R[i])){
				ans.emplace_back(i);
				dt -= 1;
				comp -= 1;
			}
		}
	}
	if(ds > 0 and dt > 0 and joined){
		if(join(s, t)){
			ans.emplace_back(joined);
			ds -= 1;
			dt -= 1;
			comp -= 1;
		}
	}
	if(comp > 1){
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=0; i<ans.size(); i++){
		int x = ans[i];
		printf("%d %d\n", L[x], R[x]);
	}
	return 0;
}
