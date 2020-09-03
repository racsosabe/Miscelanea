#include<bits/stdc++.h>
using namespace::std;

long long a, b;

int main(){
	scanf("%lld %lld", &a, &b);
	int pos = -1;
	for(int i = 61; i >= 0; i--){
		if(((a >> i) & 1) ^ ((b >> i) & 1)){
			pos = i;
			break;
		}
	}
	printf("%lld\n", (1LL << (pos + 1)) - 1);
	return 0;
}
