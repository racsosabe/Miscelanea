#include<bits/stdc++.h>
using namespace::std;

int n;
string s;

int main(){
	cin >> s;
	n = s.size();
	if(s == "0"){
		puts("0");
		return 0;
	}
	int ans = 0;
	for(int i = 0; i < s.size(); i++){
		if(s[i] != '9'){
			int d = s[i] - '0';
			ans += min(1 + (10 - d), d);
			s[i] = ' ';
		}
	}
	for(int i = 0; i < s.size(); i++){
		if(s[i] == '9' and (i == 0 or s[i - 1] != '9')) ans += 2;
	}
	printf("%d\n", ans);
	return 0;
}
