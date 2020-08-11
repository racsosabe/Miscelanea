#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000+5;

int x;
int p;
int k;
int len;
vector<int> v;
int mobius[N];
bool composite[N];

void init(){
	mobius[1] = 1;
	vector<int> primes;
	for(int i = 2; i < N; i++){
		if(not composite[i]){
			mobius[i] = -1;
			primes.emplace_back(i);
		}
		for(int p : primes){
			if(i * p >= N) break;
			composite[i * p] = true;
			if(i % p == 0){
				mobius[i * p] = 0;
				break;
			}
			else{
				mobius[i * p] = -mobius[i];
			}
		}
	}
}

void getDivisors(){
	v.clear();
	if(p > 1 and mobius[p]) v.emplace_back(p);
	for(int i = 2; i * i <= p; i++){
		if(p % i == 0){
			if(mobius[i]) v.emplace_back(i);
			if(i * i != p and mobius[p / i]) v.emplace_back(p / i);
		}
	}
}

long long f(long long a){
	long long lesseq = 0;
	for(int d : v){
		lesseq -= (a / d) * mobius[d];
	}
	return a - lesseq;
}

int main(){
	int t;
	init();
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &x, &p, &k);
		getDivisors();
		long long lo = x + 1, hi = 1e12;
		while(lo < hi){
			long long mi = lo + (hi - lo) / 2;
			if(f(mi) - f(x) < k) lo = mi + 1;
			else hi = mi;
		}
		printf("%lld\n",lo);
	}
	return 0;
}

