#include<bits/stdc++.h>
using namespace::std;

const int N = 20;

int n, l, r, x;
int v[N];

int main(){
	scanf("%d %d %d %d", &n, &l, &r, &x);
	for(int i = 0; i < n; i++) scanf("%d", &v[i]);
	int ans = 0;
	for(int i = 0; i < 1<<n; i++){
		int minimo = INT_MAX;
		int maximo = 0;
		int total = 0;
		for(int j = 0; j < n; j++){
			if((i >> j) & 1){
				minimo = min(minimo, v[j]);
				maximo = max(maximo, v[j]);
				total += v[j];
			}
		}
		if(total >=l and total <= r and maximo-minimo >= x) ans += 1;
	}
	printf("%d\n", ans);
	return 0;
}
