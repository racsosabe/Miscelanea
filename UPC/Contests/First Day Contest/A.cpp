#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int LOG = 20;

int n;
int C;
int len;
int a[N];
int b[N];
int w[N * LOG];
int v[N * LOG];
int nxt[N * LOG];
long long memo[N * LOG][N];

void getValues(){
	for(int i = 0; i < n; i++){
		int L = len;
		w[len] = a[i];
		v[len++] = b[i];
		b[i] >>= 1;
		while(b[i] > 0){
			w[len] = a[i];
			v[len++] = b[i];
			b[i] >>= 1;
		}
		for(int j = L; j < len; j++) nxt[j] = len;
	}
}

long long solve(){
	for(int pos = len - 1; pos >= 0; pos--){
		for(int left = 0; left <= C; left++){
			long long ans = memo[nxt[pos]][left];
			if(left >= w[pos]){
				long long cand = v[pos] + memo[pos + 1][left - w[pos]];
				if(ans < cand) ans = cand;
			}
			memo[pos][left] = ans;
		}
	}
	return memo[0][C];
}

int main(){
	scanf("%d %d", &n, &C);
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
	}
	for(int i = 0; i < n; i++){
		scanf("%d", b + i);
	}
	getValues();
	printf("%lld\n", solve());
	return 0;
}
