#include<bits/stdc++.h>
using namespace::std;

string s;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int zeros = 0;
	cin >> s;
	int maximo = 0;
	for(int i = s.size() - 1; i>=0; i--){
		if(s[i] == '0') zeros++;
		if(s[i] == '1') maximo = max(maximo, zeros);
	}
	cout << (maximo >= 6? "yes" : "no") << '\n';
	return 0;
}

