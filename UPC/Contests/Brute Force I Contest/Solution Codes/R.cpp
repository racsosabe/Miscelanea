#include<bits/stdc++.h>
using namespace::std;

const string target = "nineteen";

string s;
int F[27];
int Q[27];


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	for(auto x : s){
		Q[x - 'a']++;
	}
	for(auto x : target){
		F[x - 'a']++;
	}
	int pos = 0;
	int ans = 0;
	while(true){
		if(Q[target[pos] - 'a'] > 0){
			Q[target[pos] - 'a']--;
			pos++;
			if(pos == target.size()){
				pos = 1;
				ans++;
			}
		}
		else break;
	}
	cout << ans << endl;
	return 0;
}

