#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

struct DSegTree{
	int xmin;
	int xmax;
	int nodes;
	vector<int> st;
	vector<int> L, R;

	DSegTree(){
		xmin = -1e8;
		xmax = 1e8;
		nodes = 0;
		addNode();
	}

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
		int mi = l + (r - l) / 2;
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
		st[pos] = max((L[pos] >= 0? st[L[pos]] : 0), (R[pos] >= 0? st[R[pos]] : 0));
	}

	int query(int x, int y, int pos, int l, int r){
		if(y < l or r < x or x > y or pos == -1) return 0;
		if(x <= l and r <= y) return st[pos];
		int mi = l + (r - l) / 2;
		return max(query(x, y, L[pos], l, mi), query(x, y, R[pos], mi + 1, r));
	}

	void update(int x, int y){
		update(x, y, 0, xmin, xmax);
	}

	int query(int x, int y){
		return query(x, y, 0, xmin, xmax);
	}
};	

int n;
int h[N];
int x[N];
int ans[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &x[i], &h[i]);
	}
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return x[i] < x[j];
	});
	DSegTree st;
	for(int i = n-1; i >= 0; i--){
		int l = x[p[i]];
		int r = x[p[i]] + h[p[i]] - 1;
		ans[p[i]] = max(st.query(l, r) - i, 0) + 1;
		st.update(x[p[i]], i + ans[p[i]] - 1);
	}
	for(int i = 1; i <= n; i++){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
