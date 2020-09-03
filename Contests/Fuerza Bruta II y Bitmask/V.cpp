#include<bits/stdc++.h>
using namespace::std;

const int N = 30+5;
const long long inf = 1e18;

int n;
int L;
int values[N];
long long memo[N];

long long getVal(int pos){
	if(pos > n-1){
		return (1LL << (pos - n + 1)) * memo[n - 1];
	}
	else{
		return memo[pos];
	}
}

long long solve(){
	long long ans = inf;
	long long suma = 0LL;
	for(int i = 31; i >= 0; i--){
		if((L >> i) & 1) suma += getVal(i);
		if(!((L >> i) & 1)){
			ans = min(ans,suma + getVal(i));
		}
		L %= 1 << i;
		if(L == 0){
			ans = min(ans, suma);
		}
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &L);
	for(int i = 0; i < n; i++){
		scanf("%d", values + i);
		memo[i] = values[i];
	}
	for(int i = 1; i < n; i++){
		for(int j = 0; j < i; j++){
			memo[i] = min(memo[i], (1LL << (i - j)) * memo[j]);
		}
	}
	long long ans = solve();
	printf("%lld\n", ans);
	return 0;
}
