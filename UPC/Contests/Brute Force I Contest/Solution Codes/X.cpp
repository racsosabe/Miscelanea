#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;

int n, t;
int a[N];

int main(){
	scanf("%d %d", &n, &t);
	int ans = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
		a[i] = 86400 - a[i];
		t -= a[i];
		if(ans == 0 and t <= 0) ans = i;
	}
	printf("%d\n", ans);
	return 0;
}

