#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
	scanf("%d", &n);
	double ans = 0.0;
	for(int i = 1; i <= n; i++){
		ans += 1.0 * i * (i - 1) / n;
	}
	printf("%.7lf\n", ans);
	return 0;
}
