#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;
const int inf = 2e9;

int n, k;
int a[N];
int prefix[N];
int suffix[N];

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	if(k == 1){
		printf("%d\n",*min_element(a + 1, a + n + 1));
	}
	else if(k == 2){
		prefix[0] = inf;
		suffix[n+1] = inf;
		for(int i = 1; i <= n; i++){
			prefix[i] = min(a[i], prefix[i - 1]);
		}
		for(int i = n; i >= 1; i--){
			suffix[i] = min(a[i], suffix[i + 1]);
		}
		int ans = -inf;
		for(int i = 1; i < n; i++){
			ans = max({prefix[i], suffix[i + 1], ans});
		}
		printf("%d\n",ans);
	}
	else{
		printf("%d\n",*max_element(a + 1, a + n + 1));
	}
	return 0;
}

