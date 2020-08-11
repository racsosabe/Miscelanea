#include<bits/stdc++.h>
using namespace::std;

string s;

bool palindrome(string x){
	string y = x;
	reverse(y.begin(), y.end());
	return x==y;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	while(palindrome(s)){
		if(s.size() == 1){
			s = "";
			break;
		}
		else{
			s = s.substr(1);
		}
	}
	cout << s.size() << endl;
	return 0;
}

