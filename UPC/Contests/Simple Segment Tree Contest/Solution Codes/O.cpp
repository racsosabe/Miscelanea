#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int inf = 1e9;
 
struct DSegTree{
	int n;
	int nodes;
	vector<int> st;
	vector<int> L, R;
 
	DSegTree(){
		nodes = 0;
		n = 100000 + 1;
		addNode();
	};
 
	void addNode(){
		st.emplace_back(0);
		L.emplace_back(-1);
		R.emplace_back(-1);
		nodes += 1;
	}
 
	void update(int x, int y, int pos, int l, int r){
		if(l == r){
			st[pos] = max(st[pos], y);
			return;
		}
		int mi = (l + r) / 2;
		if(l <= x and x <= mi){
			if(L[pos] == -1){
				L[pos] = nodes;
				addNode();
			}
			update(x, y, L[pos], l, mi);
		}
		else{
			if(R[pos] == -1){
				R[pos] = nodes;
				addNode();
			}
			update(x, y, R[pos], mi + 1, r);
		}
		int Lans = L[pos] >= 0? st[L[pos]] : -inf;
		int Rans = R[pos] >= 0? st[R[pos]] : -inf;
		st[pos] = max(Lans, Rans);
	}
 
	int query(int x, int y, int pos, int l, int r){
		if(y < l or r < x or x > y){
			return 0;
		}
		if(pos == -1) return 0;
		if(x <= l and r <= y){
			return st[pos];
		}
		int mi = (l + r) / 2;
		return max(query(x, y, L[pos], l, mi), query(x, y, R[pos], mi+1, r));
	}
 
	void update(int x, int y){
		update(x, y, 0, 0, n);
	}
 
	int query(int x){
		return query(0, x, 0, 0, n);
	}
};
 
int n, m;
int a[N];
int b[N];
int w[N];
int memo[N];
int best[N];
DSegTree st[N];
 
int main(){
	scanf("%d %d", &n, &m);
	int ans = 0;
	for(int i = 1; i <= m; i++){
		scanf("%d %d %d", &a[i], &b[i], &w[i]);
		a[i] ^= ans;
		b[i] ^= ans;
		w[i] ^= ans;
		w[i] += 1;
		int cur_best = 1 + st[a[i]].query(w[i]-1);
		ans = max(ans, cur_best);
		printf("%d\n", ans);
		st[b[i]].update(w[i], cur_best);
	}
	return 0;
}
