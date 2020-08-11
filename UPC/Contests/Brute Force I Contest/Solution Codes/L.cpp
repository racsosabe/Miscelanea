#include<bits/stdc++.h>
using namespace::std;

const int N = 300000+5;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	sort(a + 1, a + n + 1);
	printf("%d\n", a[(n + 1) / 2]);
	return 0;
}

