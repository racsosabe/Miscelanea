#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int m;
int q;
int v[N];
int a[N];
int b[N];
int ans[N];
int par[N];
bool vis[N];
int sizes[N];

void create(int x){
	par[x] = x;
	sizes[x] = 1;
}

int get(int x){
	return par[x] == x? x : par[x] = get(par[x]);
}

bool join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return false;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
	return true;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++){
		scanf("%d %d", &a[i], &b[i]);
	}
	scanf("%d", &q);
	for(int i=1; i<=q; i++){
		scanf("%d", &v[i]);
		vis[v[i]] = true;
	}
	for(int i=1; i<=n; i++) create(i);
	int cur = n;
	for(int i=1; i<=m; i++){
		if(vis[i]) continue;
		if(join(a[i], b[i])) cur -= 1;
	}
	for(int i=q; i>=1; i--){
		ans[i] = cur;
		if(join(a[v[i]], b[v[i]])) cur -= 1;
	}
	for(int i=1; i<=q; i++){
		printf("%d%c",ans[i]," \n"[i == q]);
	}
	return 0;
}
