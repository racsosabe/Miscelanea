#include<bits/stdc++.h>
using namespace::std;

const int N = 10000+5;

int n;
int q;
int s[N];
int par[N];
int owner[N];
int sizes[N];

void create(int x){
	par[x] = x;
	sizes[x] = 1;
	owner[x] = x;
}

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

int join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return -1;
	if(s[owner[a]] == s[owner[b]]) return 0;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	owner[b] = s[owner[b]] > s[owner[a]]? owner[b] : owner[a];
	return 1;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i=1; i<=n; i++){
			scanf("%d", &s[i]);
			create(i);
		}
		scanf("%d",&q);
		int op, x, y;
		while(q--){
			scanf("%d", &op);
			if(op == 0){
				scanf("%d %d", &x, &y);
				int res = join(x, y);
				if(res == -1) puts("Invalid query!");
			}
			else{
				scanf("%d", &x);
				printf("%d\n", owner[get(x)]);
			}
		}
	}
	return 0;
}
