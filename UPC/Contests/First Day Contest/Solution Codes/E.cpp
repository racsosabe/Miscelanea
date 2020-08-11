#include<bits/stdc++.h>
using namespace::std;
 
int n;
char carry[5];

bool query(int x){
	printf("%d\n",x);
	fflush(stdout);
	scanf("%s", carry);
	return carry[0] == '<';
}
 
int main(){
	scanf("%d", &n);
	int lo = 1, hi = n;
	while(lo < hi){
		int mi = lo + (hi - lo + 1)/2;
		if(query(mi)) hi = mi-1;
		else lo = mi;
	}
	printf("! %d\n",lo);
	fflush(stdout);
	return 0;
}
