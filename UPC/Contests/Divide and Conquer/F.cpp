#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;

int n;
int k;
int a[N];
int needed;

bool can(int x){
	int gt = 0;
	int eq = 0;
	for(int i=1; i<=n; i++){
		if(a[i] > x) gt++;
		if(a[i] == x) eq++;
	}
	if(gt > needed) return false;
	long long steps = 0LL;
	for(int i=n; i>=1; i--){
		if(gt + eq <= needed and a[i] < x){
			steps += x - a[i];
			eq += 1;
		}
	}
	if(gt + eq <= needed) return false;
	return steps <= 1LL * k;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++) scanf("%d",a+i);
	sort(a+1,a+1+n);
	needed = n / 2;
	int lo = a[n/2 + 1], hi = 2000000000;
	while(lo < hi){
		int mi = lo + (hi-lo + 1)/2;
		if(can(mi)) lo = mi;
		else hi = mi-1;
	}
	printf("%d\n",lo);
	return 0;
}
