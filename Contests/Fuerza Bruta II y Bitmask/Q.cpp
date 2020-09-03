#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000+5;
const int MASK = 1<<26;
const int E = 26;

int n;
char s[N];
int F[MASK];

int main(){
	scanf("%d", &n);
	scanf("%s", s + 1);
	F[0] = 1;
	int cur_mask = 0;
	long long ans = 0LL;
	for(int i = 1; i <= n; i++){
		cur_mask ^= 1 << (s[i] - 'a');
		ans += F[cur_mask];
		for(int j = 0; j < E; j++){
			int mask_needed = cur_mask ^ (1<<j);
			ans += F[mask_needed];
		}
		F[cur_mask] += 1;
	}
	printf("%lld\n", ans);
	return 0;
}

