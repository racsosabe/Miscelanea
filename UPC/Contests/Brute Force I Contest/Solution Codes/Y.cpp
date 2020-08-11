#include<bits/stdc++.h>
using namespace::std;

inline int mul(int a, int b, int m){
	return (1LL * a * b) % m;
}

inline int add(int a, int b, int m){
	return (a + b) % m;
}

int k, p;

string toString(int x){
	string ans = "";
	while(x > 0){
		ans += char('0' + x % 10);
		x /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int solve(string s){
	int ans = 0;
	for(int i = 0; i < s.size(); i++){
		ans = add(mul(ans,10,p),s[i]-'0',p);
	}
	return ans;
}

int getNumber(int x){
	string s = toString(x);
	string y = s;
	reverse(y.begin(), y.end());
	s += y;
	return solve(s);
}

int main(){
	scanf("%d %d", &k, &p);
	int ans = 0;
	for(int i = 1; i <= k; i++){
		ans = add(ans, getNumber(i), p);
	}
	printf("%d\n", ans);
	return 0;
}

