#include<bits/stdc++.h>
using namespace::std;

string a;
string b;

void transform(string &s){
	for(int i = 0; i < s.size(); i++){
		if(s[i] <= 'Z') s[i] += 'a' - 'A';
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b;
	transform(a);
	transform(b);
	if(a == b) puts("0");
	else puts(a < b? "-1" : "1");
	return 0;
}
