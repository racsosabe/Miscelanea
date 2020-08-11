#include<bits/stdc++.h>
using namespace::std;

int n, m;
string ans;

void update(int l, int r, char a, char b){
	for(int i = l; i <= r; i++){
		if(ans[i] == a){
			ans[i] = b;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	cin >> ans;
	int l, r;
	char c1, c2;
	for(int i = 0; i < m; i++){
		cin >> l >> r;
		l--; r--;
		cin >> c1 >> c2;
		if(c1 == c2) continue;
		else update(l, r, c1, c2);
	}
	cout << ans << endl;
	return 0;
}

