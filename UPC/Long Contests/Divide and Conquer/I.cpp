#include<bits/stdc++.h>
using namespace::std;

int n;
char s[5];
int memo[1<<25];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s",s);
		int mask = 0;
		for(int j=0; j<3; j++){
			mask |= 1<<(s[j]-'a');
		}
		for(int m = mask; m > 0; m = mask & (m-1)){
			memo[m] += 1;
		}
	}
	for(int mask = 0; mask < 1<<24; mask++){
		memo[mask] = memo[mask&(mask-1)] + memo[(-mask)&mask];
	}
	int ans = 0;
	for(int mask = 0; mask < 1<<24; mask++){
		ans ^= memo[mask] * memo[mask];
	}
	cout << ans << endl;
	return 0;
}
