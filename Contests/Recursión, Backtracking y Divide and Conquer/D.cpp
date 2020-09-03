#include<bits/stdc++.h>
using namespace::std;

pair<int, bool> solve(){
	int wl, dl, wr, dr;
	scanf("%d %d %d %d", &wl, &dl, &wr, &dr);
	bool can = true;
	if(wl == 0){
		pair<int, bool> L = solve();
		can &= L.second;
		wl = L.first;
	}
	if(wr == 0){
		pair<int, bool> R = solve();
		can &= R.second;
		wr = R.first;
	}
	can &= wl * dl == wr * dr;
	return make_pair(wl + wr, can);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		pair<int, bool> ans = solve();
		puts(ans.second? "YES" : "NO");
		if(t) puts("");
	}	
	return 0;
}
