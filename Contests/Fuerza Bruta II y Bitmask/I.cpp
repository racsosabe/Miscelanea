#include<bits/stdc++.h>
using namespace::std;

const int MASK = 1<<10;

int n;
int m;
bool play[MASK];

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &m);
		for(int i = 0; i < 1<<n; i++) play[i] = true;
		for(int i = 0; i < m; i++){
			int x;
			scanf("%d", &x);
			x -= 1;
			play[x] = false;
		}
		int ans = 0;
		for(int len = 1; len < 1<<n; len <<= 1){
			for(int i = 0; i + len < 1<<n; i += 2 * len){
				if(play[i] ^ play[i + len]){
					ans += 1;
				}
				play[i] |= play[i + len];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
