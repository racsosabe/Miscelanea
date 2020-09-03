#include<bits/stdc++.h>
using namespace::std;

const int N = 8000 + 5;

int n;
int T;
int L[N];
int R[N];
int in[N];
int pre[N];
int post[N];
int my_post[N];
int inorder[N];

int build(int l, int r){
	if(l > r) return - 1;
	int u = pre[T++];
	int mi = inorder[u];
	L[u] = build(l, mi - 1);
	R[u] = build(mi + 1, r);
	return u;
}

void getPost(int u){
	if(L[u] != -1){
		getPost(L[u]);
	}
	if(R[u] != -1){
		getPost(R[u]);
	}
	my_post[T++] = u;
}

bool check(){
	for(int i = 0; i < n; i++){
		if(post[i] != my_post[i]) return false;
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &pre[i]);
	}
	for(int i = 0; i < n; i++){
		scanf("%d", &post[i]);
	}
	for(int i = 0; i < n; i++){
		scanf("%d", &in[i]);
		inorder[in[i]] = i;
	}
	memset(L, -1, sizeof L);
	memset(R, -1, sizeof R);
	int root = build(0, n - 1);
	T = 0;
	getPost(root);
	puts(check()? "yes" : "no");
	return 0;
}
