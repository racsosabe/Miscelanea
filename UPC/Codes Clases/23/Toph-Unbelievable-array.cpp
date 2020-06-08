#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;
const int m = 100000;

struct DSU{
	vector<int> col;
	vector<int> par;
	vector<int> sizes;
	DSU(){};

	DSU(int n){
		col.resize(n + 1);
		par.resize(n + 1);
		col.assign(n + 1, -1);
		sizes.resize(n + 1);
		sizes.assign(n + 1, 1);
		iota(par.begin(), par.end(), 0);
	}

	int get(int x){
		return par[x] == x? x : par[x] = get(par[x]);
	}

	void join(int a, int b){
		a = get(a);
		b = get(b);
		if(a == b) return;
		if(sizes[a] > sizes[b]) swap(a, b);
		par[a] = b;
		sizes[b] += sizes[a];
	}
};	

int n;
int q;
int a[N];
int last[N];

int main(){
	int t;
	int caso = 1;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &q);
		for(int i=1; i<=m; i++) last[i] = -1;
		DSU Nodes(n);
		for(int i=1; i<=n; i++){
			scanf("%d", &a[i]);
			if(last[a[i]] == -1){
				last[a[i]] = i;
				Nodes.col[i] = a[i];
			}
			else{
				Nodes.join(last[a[i]], i);
				Nodes.col[Nodes.get(i)] = a[i];
			}
		}
		int op, x, y;
		printf("Case %d:\n",caso++);
		while(q--){
			scanf("%d", &op);
			if(op == 1){
				scanf("%d %d", &x, &y);
				if(last[x] != -1){
					if(last[y] != -1 and last[x] != last[y]){
						Nodes.join(last[x], last[y]);
						Nodes.col[Nodes.get(last[x])] = y;
						last[x] = -1;
					}
					else{
						swap(last[x], last[y]);
						Nodes.col[Nodes.get(last[y])] = y;
					}
				}
			}
			else{
				scanf("%d", &x);
				printf("%d\n", Nodes.col[Nodes.get(x)]);
			}
		}
	}
	return 0;
}
