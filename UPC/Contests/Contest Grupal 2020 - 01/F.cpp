#include<bits/stdc++.h>
using namespace::std;

const int N = 1000+5;

int n;
int a[N];
int b[N];
bool vis[N][N];
bool memo[N][N];
int st[4 * N];

void update(int x, int y, int pos = 1, int l = 0, int r = n - 1){
	if(l == r){
		st[pos] += y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= x and x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
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

void process(){
	for(int i = 0; i < n; i++) update(i, 1);
	for(int i = 0; i + 1 < n; i++) update(b[i], -1);
	memo[n - 1][getKth(1)] = true;
	for(int step = n - 2; step >= 0; step--){
		int len = n - step;
		for(int pos = 0; pos < n; pos++){
			update(b[step], 1);
			if(query(pos, pos) == 0){
				memo[step][pos] = false;
				update(b[step], -1);
				continue;
			}
			int position = query(0, pos) - 1;
			position += a[step];
			position %= len;
			int finalpos = getKth(position + 1);
			if(query(finalpos, finalpos)){
				memo[step][pos] |= memo[step + 1][finalpos];
			}
			position = query(0, pos) - 1;
			position -= a[step];
			position %= len;
			if(position < 0) position += len;
			finalpos = getKth(position + 1);
			if(query(finalpos, finalpos)){
				memo[step][pos] |= memo[step + 1][finalpos];
			}
			update(b[step], -1);
		}
		update(b[step], 1);
	}
}

int main(){
	int p;
	scanf("%d %d", &n, &p);
	p -= 1;
	for(int i = 0; i + 1 < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i + 1 < n; i++){
		scanf("%d", &b[i]);
		b[i] -= 1;
	}
	process();
	puts(memo[0][p]? "Yes" : "No");
	return 0;
}
