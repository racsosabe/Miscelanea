#include<bits/stdc++.h>
using namespace::std;

int n;
string s;

int main(){
	cin >> s;
	n = s.size();
	reverse(s.begin(), s.end());
	int ans = 0;
	for(int i=0; i<s.size(); i++){
		int x = s[i] - '0';
		int cur = x&1;
		int nxt = x / 2;
		if(nxt){
			if(i+1 < s.size()) s[i+1] += 1;
			else s += '1';
		}
		if(cur){
			ans += 2;
			s[i+1] += 1;
		}
		else ans += 1;
	}
	ans -= 2;
	printf("%d\n",ans);
	return 0;
}
