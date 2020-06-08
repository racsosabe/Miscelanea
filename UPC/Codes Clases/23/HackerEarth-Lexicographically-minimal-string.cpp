#include<bits/stdc++.h>
using namespace::std;

const int E = 256;
const int N = 100000+5;

int n;
int m;
char a[N];
char b[N];
char c[N];
int par[E];
int best[E];
int sizes[E];

void create(int x){
	par[x] = x;
	best[x] = x;
	sizes[x] = 1;
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
	best[b] = min(best[a], best[b]);
}

int main(){
	scanf("%s %s %s", a, b, c);
	n = strlen(a);
	m = strlen(c);
	for(int i=0; i<E; i++) create(i);
	for(int i=0; i<n; i++){
		join(a[i], b[i]);
	}
	for(int i=0; i<m; i++){
		putchar(best[get(c[i])]);
	}
	puts("");
	return 0;
}
