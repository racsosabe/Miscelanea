#include<bits/stdc++.h>
using namespace::std;
 
const int MOD = 1000000000+7;

inline int mul(int a, int b, int m = MOD){
	return (1LL * a * b) % m;
}

inline int pow_mod(int a, int b, int m = MOD){
	int r = 1 % m;
	while(b > 0){
		if(b & 1) r = mul(r, a, m);
		a = mul(a, a, m);
		b >>= 1;
	}
	return r;
}

int k;
string s;
 
int getDigitalRoot(int x){
	if(x < 10) return x;
	int sum = 0;
	while(x > 0){
		sum += x % 10;
		x /= 10;
	}
	return getDigitalRoot(sum);
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s >> k;
	int sum = 0;
	for(int i = 0; i < s.size(); i++){
		sum += s[i] - '0';
	}
	int root = getDigitalRoot(sum);
	cout << pow_mod(root, k) << '\n';
	return 0;
}
