#include<bits/stdc++.h>
using namespace::std;

long long A, B;

int main(){
	int t;
	int caso = 1;
	scanf("%d", &t);
	while(t--){
		scanf("%lld %lld", &A, &B);
		long long common = 0LL;
		int pos = -1;
		for(int i = 61; i >= 0; i--){
			if(((A >> i) & 1) ^ ((B >> i) & 1)){
				pos = i;
				break;
			}
			common |= ((A >> i) & 1LL) << i;
		}
		long long AND = common, OR = common;
		if(pos >= 0){
			OR |= (1LL << (pos + 1)) - 1;
		}
		printf("Case %d: %lld %lld\n", caso++, OR, AND);
	}
	return 0;
}
