#include<bits/stdc++.h>
using namespace::std;

const int L = 24;
const int N = 1<<24;

int n;
char s[5];
int memo[N];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", s);
		int mask = 0;
		for(int j = 0; j < 3; j++){
			mask |= 1<<(s[j]-'a');
		}
		memo[mask] += 1;
	}
	for(int i = 0; i < L; i++){
		for(int mask = 0; mask < N; mask++){
			if(mask & (1<<i))
				memo[mask] += memo[mask ^ (1<<i)];
		}
	}
	int ans = 0;
	int total = N - 1;
	for(int i = 0; i < N; i++){
		int act = n - memo[i ^ total];
		ans ^= act * act;
	}
	printf("%d\n", ans);
	return 0;
}
