#include<bits/stdc++.h>
using namespace::std;

string s;
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	int n = s.size();
	int ans = 0;
	for(int i = 0; i < n; i++){
		set<char> S;
		int pos = i;
		while(pos < n){
			if(S.count(s[pos])) break;
			S.emplace(s[pos]);
			ans++;
			pos++;
		}
	}
	cout << ans << endl;
	return 0;
}
