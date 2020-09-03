#include<bits/stdc++.h>
using namespace::std;

int main(){
	int x;
	printf("? ");
	for(int i = 0; i < 100; i++){
		printf("%d%c",i," \n"[i + 1 == 100]);
	}
	fflush(stdout);
	scanf("%d", &x);
	int ans = 0;
	ans ^= (x >> 7) << 7;
	printf("? ");
	int times = 0;
	for(int i = 1<<7; times < 100; i += 1<<7){
		printf("%d%c",i," \n"[times + 1 == 100]);
		times += 1;
	}
	fflush(stdout);
	scanf("%d", &x);
	ans ^= (x % (1<<7));
	printf("! %d\n",ans);
	fflush(stdout);
	return 0;
}
