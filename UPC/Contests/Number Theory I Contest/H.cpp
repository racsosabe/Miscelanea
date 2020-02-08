#include<bits/stdc++.h>
using namespace::std;

int n, s, t;

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d %d",&n,&s,&t);
		int x = s + t - n;
		int S = s - x;
		int T = t - x;
		printf("%d\n",max(S,T) + 1);
	}
	return 0;
}
