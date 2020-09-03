#include<bits/stdc++.h>
using namespace::std;

string getMinimalEquivalent(string s){
	int len = s.size();
	if(len & 1) return s;
	string a = getMinimalEquivalent(s.substr(0, len / 2));
	string b = getMinimalEquivalent(s.substr(len / 2));
	if(a < b) return a + b;
	else return b + a;
}

int main(){
	string a, b;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b;
	if(getMinimalEquivalent(a) == getMinimalEquivalent(b)) cout << "YES" << '\n';
	else cout << "NO" << '\n';
	return 0;
}

