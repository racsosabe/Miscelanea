#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	int S = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
		S += a[i];
	}
	if(S){
		puts("YES");
		puts("1");
		printf("1 %d\n", n);
	}
	else{
		int cur = 0;
		for(int i = 1; i < n; i++){
			cur += a[i];
			if(cur and S-cur){
				puts("YES");
				puts("2");
				printf("1 %d\n", i);
				printf("%d %d\n", i + 1, n);
				return 0;
			}
		}
		puts("NO");
	}
	return 0;
}

