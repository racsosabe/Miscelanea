#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;

int n, m;
int cnt[3];
bool used[N][N];
bool happy[3][N];

int main(){
	scanf("%d %d", &n, &m);
	int q, x;
	for(int i=0; i<2; i++){
		scanf("%d", &q);
		for(int j=0; j<q; j++){
			scanf("%d", &x);
			happy[i][x] = true;
			cnt[i]++;
		}
	}
	for(int i = 0; i < 1e6; i++){
		int x = i % n;
		int y = i % m;
		if(happy[0][x] or happy[1][y]){
			if(!happy[0][x]){
				happy[0][x] = true;
				cnt[0]++;
			}
			if(!happy[1][y]){
				happy[1][y] = true;
				cnt[1]++;
			}
		}
		if(cnt[0] == n and cnt[1] == m){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}

