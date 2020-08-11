#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n, m;
int a[N];
int b[N];
int u[N];
int v[N];
int par[N];
int sizes[N];
vector<int> comp[N];
vector< pair<int,int> > free_edges;

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
	for(int x : comp[a]){
		if(free_edges.size() > m) break;
		for(int y : comp[b]){
			if(free_edges.size() > m) break;
			if(x + 1 == y or y + 1 == x) continue;
			free_edges.emplace_back(make_pair(x, y));
		}
	}
	for(int x : comp[a]){
		comp[b].emplace_back(x);
	}
	comp[a].clear();
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++){
		scanf("%d %d", &a[i], &b[i]);
	}
	vector<int> p(m);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(a[i] == a[j]) return b[i] > b[j];
		return a[i] < a[j];
	});
	for(int i=1; i<=n; i++){
		par[i] = i;
		sizes[i] = 1;
		comp[i].emplace_back(i);
	}
	int pos = 1;
	for(int i : p){
		if(b[i]){
			u[i] = pos;
			v[i] = pos + 1;
			join(pos, pos + 1);
			pos += 1;
		}
		else{
			if(free_edges.empty()){
				puts("-1");
				return 0;
			}
			else{
				u[i] = free_edges.back().first;
				v[i] = free_edges.back().second;
				free_edges.pop_back();
			}
		}
	}
	if(sizes[get(1)] < n){
		puts("-1");
	}
	else{
		for(int i = 1; i <= m; i++){
			printf("%d %d\n", u[i], v[i]);
		}
	}
	return 0;
}
