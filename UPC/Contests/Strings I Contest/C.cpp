#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 99999;
const int N = 250 + 5;
const int B = 311;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(int a, int b){
	return (1LL * a * b) % MOD;
}

int n;
int m;
int pot[N];
char s[N][N];
int hsh[N][N];
int mask[N][N];

void init(){
	pot[0] = 1;
	for(int i = 1; i <= 26; i++){
		pot[i] = mul(pot[i - 1], B);
	}
}

void preprocess(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			hsh[i][j] = add(hsh[i][j - 1], pot[s[i][j] - 'a' + 1]);
			mask[i][j] = mask[i][j - 1] ^ (1 << (s[i][j] - 'a'));
		}
	}
}

int manacher(vector<int> v){
	int len = v.size();
	vector<int> d1(len, 1);
	int l = 0, r = 0;
	for(int i = 0; i < len; i++){
		d1[i] = min(r - i + 1, d1[l + r - i]);
		if(d1[i] < 1) d1[i] = 1;
		while(i >= d1[i] and i + d1[i] < len and v[i - d1[i]] == v[i + d1[i]]) d1[i] += 1;
		d1[i] -= 1;
		if(i + d1[i] > r){
			l = i - d1[i];
			r = i + d1[i];
		}
	}
	vector<int> d2(len, 0);
	l = 0; r = -1;
	for(int i = 0; i < len; i++){
		d2[i] = min(r - i + 1, d2[l + r - i + 1]);
		if(d2[i] < 0) d2[i] = 0;
		while(i >= d2[i] + 1 and i + d2[i] < len and v[i - d2[i] - 1] == v[i + d2[i]]) d2[i] += 1;
		d2[i] -= 1;
		if(i + d2[i] > r){
			l = i - d2[i] - 1;
			r = i + d2[i];
		}
	}
	int ans = 0;
	for(auto x : d1){
		ans += x + 1;
	}
	for(auto x : d2){
		ans += x + 1;
	}
	return ans;
}

int solve(int c1, int c2){
	vector<int> values;
	int L = 1, R = 1;
	int ans = 0;
	while(L <= n){
		while(L <= n and __builtin_popcount(mask[L][c2] ^ mask[L][c1 - 1]) > 1){
			L += 1;
		}
		if(L > n) break;
		R = L;
		values.clear();
		while(R <= n and __builtin_popcount(mask[R][c2] ^ mask[R][c1 - 1]) <= 1){
			values.emplace_back(add(hsh[R][c2], MOD - hsh[R][c1 - 1]));
			R += 1;
		}
		ans += manacher(values);
		L = R;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	init();
	preprocess();
	long long ans = 0;
	for(int c1 = 1; c1 <= m; c1++){
		for(int c2 = c1; c2 <= m; c2++){
			ans += solve(c1, c2);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
