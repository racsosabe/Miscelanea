#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
int a[N];
int b[N];

int main(){
	scanf("%d", &n);
	long long suma = 0LL;
	for(int i=0; i<n; i++){
		scanf("%d", a + i);
		suma += a[i];
	}
	for(int i=0; i<n; i++){
		scanf("%d", b + i);
	}
	sort(b, b + n);
	if(b[n-1] + b[n-2] >= suma) puts("YES");
	else puts("NO");
	return 0;
}
