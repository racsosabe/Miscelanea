#include<bits/stdc++.h>
using namespace::std;

int n, k;

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &k);
		if(2 * k >= n) puts("Ayoub");
		else puts("Kilani");
	}
	return 0;
}
