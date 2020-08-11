#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
	scanf("%d", &n);
	int suma = 0;
	bool impar = false;
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		x &= 1;
		if(x) impar = true;
		suma += x;
		suma &= 1;
	}
	if(suma) puts("First");
	else{
		puts(impar? "First" : "Second");
	}
	return 0;
}

