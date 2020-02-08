#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;

int t;
int n, k;
int a[N];

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&k);
		int L = 1, R = INT_MAX;
		for(int i=1; i<=n; i++){
			scanf("%d",a+i);
			int l = max(1,a[i] - k);
			int r = a[i] + k;
			L = max(L,l);
			R = min(R,r);
		}
		if(L <= R) cout << R << endl;
		else puts("-1");
	}	
	return 0;
}
