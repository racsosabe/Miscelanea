#include<bits/stdc++.h>
using namespace::std;

struct DSegTree{
	int xmin;
	int xmax;
	int nodes;
	vector<int> st, L, R;

	DSegTree(){
		xmin = -1e9;
		xmax = 1e9;
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
			st[pos] = y;
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
			update(x, y, R[pos], mi+1, r);
		}
		st[pos] = (L[pos] >= 0? st[L[pos]] : 0) + (R[pos] >= 0? st[R[pos]] : 0);
	}

	int query(int x, int y, int pos, int l, int r){
		if(y < l or r < x or x > y) return 0;
		if(pos == -1) return 0;
		if(x <= l and r <= y) return st[pos];
		int mi = l + (r - l) / 2;
		return query(x, y, L[pos], l, mi) + query(x, y, R[pos], mi+1, r);
	}

	int getKth(int k, int pos, int l, int r){
		if(pos == -1 or st[pos] < k) return -1;
		if(l == r){
			return l;
		}
		int mi = l + (r - l) / 2;
		if(L[pos] != -1 and st[L[pos]] >= k) return getKth(k, L[pos], l, mi);
		else return getKth(k - (L[pos] >= 0? st[L[pos]] : 0), R[pos], mi+1, r);
		return -1;
	}

	int getKth(int k){
		return getKth(k, 0, xmin, xmax);
	}

	int query(int x){
		return query(xmin, x - 1, 0, xmin, xmax);
	}

	int count(int x){
		return query(x, x, 0, xmin, xmax);
	}

	void update(int x, int y){
		update(x, y, 0, xmin, xmax);
	}
};

int q;
DSegTree S;

int main(){
	scanf("%d", &q);
	int x;
	while(q--){
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		scanf("%d", &x);
		if(c == 'I'){
			int inside = S.count(x);
			if(!inside) S.update(x, 1);
		}
		else if(c == 'D'){
			int inside = S.count(x);
			if(inside) S.update(x, 0);
		}
		else if(c == 'K'){
			int res = S.getKth(x);
			if(res == -1) puts("invalid");
			else printf("%d\n", res);
		}
		else{
			printf("%d\n", S.query(x));
		}
	}
	return 0;
}
