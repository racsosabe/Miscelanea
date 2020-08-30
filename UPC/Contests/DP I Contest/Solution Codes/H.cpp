#include<bits/stdc++.h>
using namespace::std;

const int MOD = 998244353;
const int M = 1000000+5;
const int N = 1000+5;

int add(int a, int b, int m = MOD){
	return (a + b) % m;
}

int mul(int a, int b, int m = MOD){
	return (1LL * a * b) % m;
}

int n;
int m;
int L[N];
int R[N];
int a[M];
int C[N][N];
bool vis[N][N];
int memo[N][N];

void compress(){
	vector<int> colors;
	for(int i = 1; i <= m; i++){
		if(i == 1 or a[i - 1] != a[i]){
			colors.emplace_back(a[i]);
		}
	}
	for(int i = 0; i < colors.size(); i++){
		a[i + 1] = colors[i];
	}
	m = colors.size();
}

void preprocess(){
	for(int i = 1; i <= m; i++){
		if(!L[a[i]]) L[a[i]] = i;
		R[a[i]] = i;
	}
	for(int i = 1; i <= m; i++){
		int minimum = n + 1;
		for(int j = i; j <= m; j++){
			if(a[j] < minimum) minimum = a[j];
			C[i][j] = minimum;
		}
	}
}

int DP(int l, int r){
	if(l > r) return 1;
	if(vis[l][r]) return memo[l][r];
	int color = C[l][r];
	int ans = 0;
	if(l <= L[color] and R[color] <= r){
		int left = 0;
		for(int a = l; a <= L[color]; a++){
			left = add(left, mul(DP(l, a - 1), DP(a, L[color] - 1)));
		}
		int right = 0;
		for(int b = R[color]; b <= r; b++){
			right = add(right, mul(DP(R[color] + 1, b), DP(b + 1, r)));
		}
		ans = mul(left, right);
		int pL = L[color];
		while(pL <= R[color]){
			while(pL <= R[color] and a[pL] == color) pL += 1;
			if(pL > R[color]) break;
			int pR = pL;
			while(pR <= R[color] and a[pR] != color) pR += 1;
			ans = mul(ans, DP(pL, pR - 1));
			pL = pR;
		}
	}
	vis[l][r] = true;
	return memo[l][r] = ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d", a + i);
	}
	compress();
	if(m > 2 * n){
		puts("0");
	}
	else{
		preprocess();
		printf("%d\n", DP(1, m));
	}
	return 0;
}
