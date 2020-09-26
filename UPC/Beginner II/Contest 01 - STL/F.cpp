#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int k;
int a[N];
set<int> unicos;
map<int, int> F;

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i < k; i++){
		F[a[i]] += 1;
		if(F[a[i]] == 1) unicos.emplace(a[i]);
		else if(F[a[i]] != 1) unicos.erase(a[i]);
	}
	for(int i = k; i <= n; i++){
		F[a[i]] += 1;
		if(F[a[i]] == 1) unicos.emplace(a[i]);
		else unicos.erase(a[i]);
		if(i - k >= 1){
			F[a[i - k]] -= 1;
			if(F[a[i - k]] == 1) unicos.emplace(a[i - k]);
			else unicos.erase(a[i - k]);
		}
		if(unicos.empty()) puts("Nothing");
		else printf("%d\n", *unicos.rbegin());
	}
	return 0;
}
