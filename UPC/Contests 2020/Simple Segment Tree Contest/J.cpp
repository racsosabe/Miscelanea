#include<bits/stdc++.h>
using namespace::std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

struct DSegTree{
	int xmin;
	int xmax;
	int nodes;
	vector<int> st;
	vector<int> L, R;
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
			st[pos] += y;
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
		if(y < l or r < x or x > y or pos == -1) return 0;
		if(x <= l and r <= y) return st[pos];
		int mi = l + (r - l) / 2;
		return query(x, y, L[pos], l, mi) + query(x, y, R[pos], mi + 1, r);
	}

	void update(int x, int y){
		update(x, y, 0, xmin, xmax);
	}

	int query(int x, int y){
		return query(x, y, 0, xmin, xmax);
	}
};

int n;
int len;
vector<iii> hor, ver;

vector<iii> joinSegments(vector<iii> &v){
	sort(v.begin(), v.end());
	int L = 0, R = 0;
	vector<iii> res;
	while(L < v.size()){
		while(R < v.size() and v[L].first == v[R].first){
			R += 1;
		}
		int pL = L;
		while(pL < R){
			int l = v[pL].second.first;
			int r = v[pL].second.second;
			while(pL < R and v[pL].second.first <= r){
				r = max(v[pL].second.second, r);
				pL += 1;
			}
			res.emplace_back(make_pair(v[L].first, make_pair(l, r)));
		}
		L = R;
	}
	return res;
}

void compressYs(){
	set<int> S;
	for(auto x : ver){
		S.emplace(x.second.first);
		S.emplace(x.second.second + 1);
	}
	for(auto x : hor){
		S.emplace(x.first);
	}
	len = 0;
	map<int, int> id;
	for(auto x : S){
		id[x] = len++;
	}
	for(auto &x : ver){
		x.second.first = id[x.second.first];
		x.second.second = id[x.second.second + 1]; // Ahora es [l, r)
	}
	for(auto &x : hor){
		x.first = id[x.first];
	}
}

long long getIntersection(){
	compressYs();
	vector< vector<ii> > changes(len, vector<ii>());
	for(auto x : ver){
		changes[x.second.first].emplace_back(make_pair(x.first, 1));
		changes[x.second.second].emplace_back(make_pair(x.first, -1));
	}
	int L = 0, R = 0;
	DSegTree st;
	long long res = 0LL;
	for(int i = 0; i < len; i++){
		for(auto x : changes[i]){
			st.update(x.first, x.second);
		}
		while(L < hor.size() and hor[L].first < i){
			L += 1;
		}
		if(L == hor.size()) break;
		if(hor[L].first > i) continue;
		R = L;
		while(R < hor.size() and hor[R].first == i){
			res += st.query(hor[R].second.first, hor[R].second.second);
			R += 1;
		}
		L = R;
	}
	return res;
}

long long getArea(vector<iii> &v){
	v = joinSegments(v);
	long long res = 0LL;
	for(auto x : v){
		res += x.second.second - x.second.first + 1;
	}
	return res;
}

long long getTotal(){
	return getArea(hor) + getArea(ver);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if(a == c){
			if(b > d) swap(b, d);
			ver.emplace_back(make_pair(a, make_pair(b, d)));
		}
		else{
			if(a > c) swap(a, c);
			hor.emplace_back(make_pair(b, make_pair(a, c)));
		}
	}
	printf("%lld\n", getTotal() - getIntersection());
	return 0;
}
