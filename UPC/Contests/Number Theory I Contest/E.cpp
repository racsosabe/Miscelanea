#include<bits/stdc++.h>
using namespace::std;

const int N = 70;

int n;
long long f[N];

int main(){
	scanf("%d",&n);
	f[0] = 1;
	f[1] = 0;
	for(int i=2; i<=n; i++){
		f[i] = 2 * f[i-2];
	}
	cout << f[n] << endl;
	return 0;
}
