#include<bits/stdc++.h>
using namespace::std;

const int N = 1000+5;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", a + i);
	}
	int ans = 0;
	for(int i = 1; i + 1 < n; i++){
		int prev = i - 1;
		int next = i + 1;
		bool extrema = false;
		if(a[prev] > a[i] and a[next] > a[i]) extrema = true;
		if(a[prev] < a[i] and a[next] < a[i]) extrema = true;
		ans += extrema;
	}
	printf("%d\n", ans);
	return 0;
}

