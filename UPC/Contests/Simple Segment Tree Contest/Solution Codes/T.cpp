#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Nice Segment Tree problem.

	- Let's make some observations to solve this problem.

	- Observation 1: One MUST pass over all the nodes in the path from A to B, 

	  so we can take them as a reference.

	- Observation 2: It makes no sense to move from our current position u to a 
	
	  further position v from B and don't refill the tank.

	- Observation 3: Thanks to 2, we can just consider going to a node v that doesn't

	  belong to the mandatory ones to refill our tank and nothing else.

	- Observation 4: Now, our problem reduces to a simple path (like D1) but with

	  some ramifications over some nodes.

	- Observation 5: We just need all the minimum costs for all the possible tank values

	  when arriving to a node, but after one step all those values will be reduced

	  by 1.

	- Observation 6: One can think of using a lazy propagation method to make the

	  substraction, but it's not needed. We will mantain a value S so that each

	  position X in our segment tree will actually represent X - S.

	  Initially S = 0, so we have a value of m with cost 0, after advancing one

	  step S increases to 1 and that previous value of m now represents m - 1,

	  which is correct.

	- Observation 7: To insert a new value X to the segment tree with the representation

	  we must insert it in position X + (current S).

	- Observation 8: If we are in a mandatory node u and try to refill our tank

	  by going to node v (in the non-mandatory subtree of u) we need at least

	  dist(u, v) of fuel (thus, we must query the minimum cost from all the values
	  
	  >= dist(u, v) + S in the segment tree), and then we will return to u by

	  consuming dist(u, v) of fuel, so we have a new possible state in u but with

	  m - dist(u, v). We must update our segment tree in position m - dist(u, v) + S

	  with the cost.

	- The final answer is the minimum of all the positions >= dist(A, B) when

	  arriving to B. If it's infinity, the answer is -1.

	- Complexity: O(n log(n + m))
*/

const int N = 1000000+5;
const long long inf = 1e18;

int n;
int m;
int a;
int b;
int len;
int c[N];
int h[N];
int par[N];
bool inpath[N];
vector<int> G[N];
vector<int> path;
long long st[8 * N];
vector< pair<int, int> > changes[N];

void build(){
	for(int i = 1; i <= 4 * len; i++){
		st[i] = inf;
	}
}

void update(int x, long long y, int pos = 1, int l = 1, int r = len){
	if(l == r){
		st[pos] = min(st[pos], y);
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = min(st[2 * pos], st[2 * pos + 1]);
}

long long query(int x, int y, int pos = 1, int l = 1, int r = len){
	if(y < l or r < x or x > y) return inf;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return min(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

void getSubtree(int x){
	queue<int> Q;
	Q.emplace(x);
	vector<int> subtree;
	h[x] = 0;
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		if(c[u] > 0) subtree.emplace_back(u);
		for(int v : G[u]){
			if(inpath[v] or h[v] != -1) continue;
			h[v] = h[u] + 1;
			Q.emplace(v);
		}
	}
	if(subtree.empty()) return;
	sort(subtree.begin(), subtree.end(), [&] (int i, int j){
		if(h[i] == h[j]) return c[i] < c[j];
		return h[i] < h[j];
	});
	for(int i = 0; i < subtree.size(); i++){
		if(i == 0 or h[subtree[i-1]] != h[subtree[i]]){
			changes[x].emplace_back(make_pair(h[subtree[i]], c[subtree[i]]));
		}
	}
}

void initPath(){
	queue<int> Q;
	Q.emplace(a);
	par[a] = -2;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			if(par[v] != -1) continue;
			par[v] = u;
			Q.emplace(v);
		}
	}
	path.clear();
	for(int x = b; x != -2; x = par[x]){
		path.emplace_back(x);
		inpath[x] = true;
	}
	reverse(path.begin(), path.end());
	for(int i = 1; i + 1 < path.size(); i++){
		getSubtree(path[i]);
	}
}

void download(int x, int steps){
	for(auto e : changes[x]){
		int need = steps + e.first;
		int to = steps + m - e.first;
		int cost = e.second;
		long long previous = query(need, len);
		if(previous == inf) continue;
		long long cur_cost = cost + previous;
		update(to, cur_cost);
	}
}

long long solve(){
	for(int i = 1; i <= n; i++){
		h[i] = -1;
		par[i] = -1;
		inpath[i] = false;
	}
	initPath();
	len = n + m;
	build();
	update(m, 0);
	for(int i = 1; i < path.size(); i++){
		download(path[i], i);
	}
	long long res = query(path.size() - 1, len);
	return res == inf? -1 : res;
}

void clearAll(){
	for(int i = 1; i <= n; i++){
		changes[i].clear();
		G[i].clear();
	}
}

int main(){
	int t;
	scanf("%d", &t);
	for(int caso = 1; caso <= t; caso++){
		scanf("%d %d %d %d", &n, &m, &a, &b);
		for(int i = 1; i <= n; i++){
			int p;
			scanf("%d %d", &p, c + i);
			G[p].emplace_back(i);
			G[i].emplace_back(p);
		}
		printf("Case #%d: %lld\n", caso, solve());
		if(caso < t) clearAll();
	}
	return 0;
}

