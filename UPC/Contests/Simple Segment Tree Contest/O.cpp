#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int LOG = 30;

int n;
int m;
int L[N];
int R[N];
int x[N];
int st[LOG][4 * N];

void update(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or st[id][pos]) return;
	if(l == r){
		st[id][pos] = 1;
		return;
	}
	int mi = (l + r) / 2;
	update(id, x, y, 2 * pos, l, mi);
	update(id, x, y, 2 * pos + 1, mi + 1, r);
	st[id][pos] = min(st[id][2 * pos], st[id][2 * pos + 1]);
}

int query(int id, int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 1;
	if(x <= l and r <= y) return st[id][pos];
	int mi = (l + r) / 2;
	return min(query(id, x, y, 2 * pos, l, mi), query(id, x, y, 2 * pos + 1, mi + 1, r));
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d %d %d", &L[i], &R[i], &x[i]);
		for(int j = 0; j < LOG; j++){
			if((x[i] >> j) & 1) update(j, L[i], R[i]);
		}
	}
	for(int i = 1; i <= m; i++){
		for(int j = 0; j < LOG; j++){
			if(query(j, L[i], R[i]) != ((x[i] >> j) & 1)){
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	for(int i = 1; i <= n; i++){
		int val = 0;
		for(int j = 0; j < LOG; j++){
			val |= query(j, i, i)<<j;
		}
		printf("%d%c", val, " \n"[i == n]);
	}
	return 0;
}
