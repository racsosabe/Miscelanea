#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int a[N];

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",a+i);
			a[i] %= 3;
		}
		int ans = 0;
		int ones = 0;
		int twos = 0;
		for(int i=1; i<=n; i++){
			if(a[i] == 0) ans += 1;
			else if(a[i] == 1) ones += 1;
			else twos += 1;	
		}
		int sum = ans;
		for(int p1 = 0; p1 <= min(twos,ones); p1++){
			int p2 = ones - p1;
			int p3 = twos - p1;
			ans = max(ans,sum + p1 + p2 / 3 + p3 / 3);
		}
		printf("%d\n",ans);
	}
	return 0;
}
