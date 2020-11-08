#include<bits/stdc++.h>
using namespace::std;

long long n;

int main(){
	scanf("%lld", &n);
	vector< pair<long long, int> > factores;
	for(int i = 2; 1LL * i * i <= n; i++){
		if(n % i == 0){
			int e = 0;
			while(n % i == 0){
				e += 1;
				n /= i;
			}
			factores.emplace_back(make_pair(i, e));
		}
	}
	if(n > 1){
		factores.emplace_back(make_pair(n, 1));
	}
	for(int i = 0; i < factores.size(); i++){
		printf("%lld^%d", factores[i].first, factores[i].second);
		if(i + 1 < factores.size()) printf(" x ");
		else printf("\n");
	}
	return 0;
}
