#include<bits/stdc++.h>
using namespace::std;

/*
	Problem: Equivalent Strings - Codeforces 559B

	Author: Racso Galvan
*/

string getMinimalEquivalent(string s){
	int len = s.size();
	if(len&1) return s;
	string a = getMinimalEquivalent(s.substr(0,len/2));
	string b = getMinimalEquivalent(s.substr(len/2,len));
	if(a < b) return a + b;
	else return b + a;
}

int main(){
	string a, b;
	cin >> a >> b;
	if(getMinimalEquivalent(a) == getMinimalEquivalent(b)) puts("YES");
	else puts("NO");
	return 0;
}
