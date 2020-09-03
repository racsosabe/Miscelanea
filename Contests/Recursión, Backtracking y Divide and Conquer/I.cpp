#include<bits/stdc++.h>
using namespace::std;

int n;

bool isSquare(int x){
	int lo = 0, hi = x;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(mi * mi < x) lo = mi + 1;
		else hi = mi;
	}
	return lo * lo == x;
}

int solve(int len){
	vector<int> v(len, -1);
	int pos = 1;
	while(true){
		int best = -1;
		for(int i = 0; i < len; i++){
			if(v[i] == -1){
				best = i;
				break;
			}
			else{
				if(isSquare(v[i] + pos)){
					best = i;
					break;
				}
			}
		}
		if(best == -1) break;
		v[best] = pos;
		pos += 1;
	}
	return pos - 1;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		printf("%d\n", solve(n));
	}	
	return 0;
}
