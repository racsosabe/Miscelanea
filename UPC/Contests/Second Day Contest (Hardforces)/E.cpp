#include<bits/stdc++.h>
using namespace::std;

string a, b;

string unique(string s){
	string ans = "0" + s;
	for(int i=ans.size()-2; i>=0; i--){
		if(ans[i] >= '1' and ans[i+1] >= '1'){
			ans[i-1] += 1;
			ans[i] -= 1;
			ans[i+1] -= 1;
		}
	}
	for(int i = 0; i+2<ans.size(); i++){
		if(ans[i] == '2'){
			ans[i-1] += 1;
			ans[i] = '0';
			ans[i+1] = '0';
			ans[i+2] += 1;
		}
	}
	int pos = 0;
	while(pos + 1 < ans.size() and ans[pos] == '0') pos++;
	ans = ans.substr(pos);
	return ans;
}

bool menor(string x, string y){
	if(x.size() > y.size()) return false;
	if(x.size() < y.size()) return true;
	return x < y;
}

bool golden(string s){
	for(int i=1; i<s.size(); i++){
		if(s[i] == '1' and s[i-1] == '1') return true;
	}
	return false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b;
	a = unique(a);
	b = unique(b);
	while(golden(a)){
		a = unique(a);
	}
	while(golden(b)){
		b = unique(b);
	}
	if(a == b) puts("=");
	else{
		if(menor(a,b)) puts("<");
		else puts(">");
	}
	return 0;
}
