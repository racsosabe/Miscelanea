#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int val;
	int cnt;
	int priority;
	node* left;
	node* right;
	node(){};
	node(int val) : val(val) {
		priority = random(0, 2000000000);
		cnt = 1;
		left = right = nullptr;
	}
};

int n;
int T;
int llim;
int wlim;
int h[N];
int a[N];
int in[N];
int out[N];
long long ans;
int subtree[N];
bool removed[N];
vector<int> G[N];
vector<int> W[N];
long long path[N];

int cnt(node* u){
	return u ? u -> cnt : 0;
}

void update(node* u){
	if(u) u -> cnt = cnt(u -> left) + cnt(u -> right) + 1;
}

pair<node*, node*> split(node* t, int x){
	if(t == nullptr){
		return {nullptr, nullptr};
	}
	if(t -> val <= x){
		pair<node*, node*> p = split(t -> right, x);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, x);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

node* merge(node* l, node* r){
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	if(l -> priority > r -> priority){
		l -> right = merge(l -> right, r);
		update(l);
		return l;
	}
	else{
		r -> left = merge(l, r -> left);
		update(r);
		return r;
	}
}

node* insert(node* u, int val){
	pair<node*, node*> p = split(u, val);
	u = merge(p.first, new node(val));
	u = merge(u, p.second);
	return u;
}

node* getLeq(node* u, int val, long long &res){
	pair<node*, node*> p = split(u, val);
	res += cnt(p.first);
	u = merge(p.first, p.second);
	return u;
}

void DFS(int u, int p = -1){
	subtree[u] = 1;
	a[T] = u;
	in[u] = T++;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int we = W[u][i];
		if(removed[v] or v == p) continue;
		h[v] = h[u] + 1;
		path[v] = path[u] + we;
		DFS(v, u);
		subtree[u] += subtree[v];
	}
	out[u] = T - 1;
}

int centroid(int u, int p, int root){
	for(int v : G[u]){
		if(removed[v] or v == p) continue;
		if(2 * subtree[v] > subtree[root]) return centroid(v, u, root);
	}
	return u;
}

long long compute(int l, int r){
	vector< pair<int, int> > values;
	node* T = nullptr;
	for(int i = l; i <= r; i++){
		int at = a[i];
		values.emplace_back(make_pair(h[at], path[at]));
	}
	sort(values.begin(), values.end());
	int pos = 0;
	long long res = 0LL;
	for(int i = values.size() - 1; i >= 0; i--){
		while(pos < values.size() and values[pos].first + values[i].first <= llim){
			T = insert(T, values[pos].second);
			pos += 1;
		}
		T = getLeq(T, wlim - values[i].second, res);
	}
	return res;
}

void solve(int u){
	T = 0;
	h[u] = path[u] = 0;
	DFS(u);
	ans += compute(in[u], out[u]);
	for(int v : G[u]){
		if(removed[v]) continue;
		ans -= compute(in[v], out[v]);
	}
}

void decompose(int u, int p = -1){
	T = 0;
	DFS(u, p);
	int c = centroid(u, u, u);
	removed[c] = true;
	solve(c);
	for(int v : G[c]){
		if(removed[v] or v == p) continue;
		decompose(v, c);
	}
}

int main(){
	scanf("%d %d %d", &n, &llim, &wlim);
	for(int i = 2; i <= n; i++){
		int p, c;
		scanf("%d %d", &p, &c);
		G[p].emplace_back(i);
		G[i].emplace_back(p);
		W[p].emplace_back(c);
		W[i].emplace_back(c);
	}
	decompose(1);
	printf("%lld\n", (ans - n) / 2);
	return 0;
}
