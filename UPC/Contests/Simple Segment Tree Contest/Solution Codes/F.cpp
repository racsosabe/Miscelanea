#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int st[4 * N];

void build(int pos = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] = 1;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

void update(int x, int pos = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] = 0;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, 2 * pos, l, mi);
	else update(x, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
}

int query(int x, int y, int pos = 1, int l = 0, int r = n - 1){
	if(y < l or r < x or x > y) return 0;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

int getKth(int k, int pos = 1, int l = 0, int r = n - 1){
	if(l == r) return l;
	int mi = (l + r) / 2;
	if(st[2 * pos] >= k) return getKth(k, 2 * pos, l, mi);
	else return getKth(k - st[2 * pos], 2 * pos + 1, mi + 1, r);
}

vector<int> getOrd(vector<int> p){
	vector<int> res;
	build();
	for(int i = 0; i < p.size(); i++){
		res.emplace_back(query(0, p[i]) - 1);
		update(p[i]);
	}
	return res;
}

vector<int> sumOrd(vector<int> a, vector<int> b){
	vector<int> res(n, 0);
	for(int i = 0; i < n; i++){
		res[i] = a[i] + b[i];
	}
	for(int i = n - 1; i >= 0; i--){
		int mod = n - i;
		if(i - 1 >= 0){
			res[i - 1] += res[i] / mod;
		}
		res[i] %= mod;
	}
	return res;
}

vector<int> getPerm(vector<int> ord){
	vector<int> res;
	build();
	for(int i = 0; i < n; i++){
		int pos = getKth(ord[i] + 1);
		update(pos);
		res.emplace_back(pos);
	}
	return res;
}

int main(){
	scanf("%d", &n);
	vector<int> a(n), b(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < n; i++) scanf("%d", &b[i]);
	vector<int> ordA = getOrd(a);
	vector<int> ordB = getOrd(b);
	vector<int> ordR = sumOrd(ordA, ordB);
	vector<int> res = getPerm(ordR);
	for(int i = 0; i < n; i++){
		printf("%d%c", res[i], " \n"[i + 1 == n]);
	}
	return 0;
}
