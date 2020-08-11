#include<bits/stdc++.h>
using namespace::std;
 
int n;
map<long long,int> F;
 
int main(){
	scanf("%d", &n);
	int ans = n;
	long long prefix = 0LL;
	int x;
	for(int i=1; i<=n; i++){
		scanf("%d", &x);
		prefix += x;
		F[prefix] += 1;	
		ans = min(ans,n-F[prefix]);
	}
	printf("%d\n", ans);
	return 0;
}
