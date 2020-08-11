#include<bits/stdc++.h>
using namespace::std;

const int N = 5000000+5;

int n;
int pf[N];
int ac[N];

void init(){
	vector<int> primes;
	for(int i = 2; i < N; i++){
		if(pf[i] == 0){
			pf[i] = 1;
			primes.emplace_back(i);
		}
		for(int p : primes){
			if(i * p >= N) break;
			pf[i * p] = 1 + pf[i];
			if(i % p == 0) break;
		}
		ac[i] = pf[i] + ac[i - 1];
	}
}

int main(){
	init();
	int t;
	scanf("%d", &t);
	while(t--){
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", ac[a] - ac[b]);
	}
	return 0;
}
