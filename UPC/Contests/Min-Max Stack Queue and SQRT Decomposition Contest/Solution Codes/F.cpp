#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int m;
int a[N];
int L[N];
int R[N];
int bsize;
int id[N];
int ans[N];
int frec[N];

void solve(vector<int> &p){
	int l = 1;
	int r = 1;
	int cnt = 0;
	for(auto x : p){
		while(r <= R[x]){
			if(a[r] != -1){
				if(frec[a[r]] == a[r]) cnt -= 1;
				frec[a[r]] += 1;
				if(frec[a[r]] == a[r]) cnt += 1;
			}
			r += 1;
		}
		while(l < L[x]){
			if(a[l] != -1){
				if(frec[a[l]] == a[l]) cnt -= 1;
				frec[a[l]] -= 1;
				if(frec[a[l]] == a[l]) cnt += 1;
			}
			l += 1;

		}
		while(l > L[x]){
			l -= 1;
			if(a[l] != -1){
				if(frec[a[l]] == a[l]) cnt -= 1;
				frec[a[l]] += 1;
				if(frec[a[l]] == a[l]) cnt += 1;
			}
		}
		while(R[x] + 1 < r){
			r -= 1;
			if(a[r] != -1){
				if(frec[a[r]] == a[r]) cnt -= 1;
				frec[a[r]] -= 1;
				if(frec[a[r]] == a[r]) cnt += 1;
			}
		}
		ans[x] = cnt;
	}
}

int main(){
	scanf("%d %d", &n, &m);
	bsize = ceil(1.0 * n / sqrt(m));
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		if(a[i] > n) a[i] = -1;
	}
	for(int i = 1; i <= m; i++){
		scanf("%d %d", &L[i], &R[i]);
		id[i] = L[i] / bsize;
	}
	vector<int> p(m);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(id[i] == id[j]) return id[i] & 1? R[i] > R[j] : R[i] < R[j];
		return id[i] < id[j];
	});
	solve(p);
	for(int i = 1; i <= m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
