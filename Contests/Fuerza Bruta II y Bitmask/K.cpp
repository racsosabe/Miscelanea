#include<bits/stdc++.h>
using namespace::std;

const int N = 1000+5;

int n, m, k, x;
int v[N];

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < m; i++){
		scanf("%d", v + i);
	}
	scanf("%d", &x);
	int ans = 0;
	for(int i = 0; i < m; i++){
		int differences = 0;
		for(int j = 0; j < n; j++){
			differences += ((x >> j) & 1) ^ ((v[i] >> j) & 1);
		}
		if(differences <= k) ans += 1;
	}
	printf("%d\n", ans);
	return 0;
}
