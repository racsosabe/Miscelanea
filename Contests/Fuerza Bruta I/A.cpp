#include<bits/stdc++.h>
using namespace::std;

const int D = 400;
 
int n;
int male[D];
int female[D];
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	char op;
	int l, r;
	for(int i=0; i<n; i++){
		cin >> op >> l >> r;
		if(op == 'M'){
			male[l] += 1;
			male[r+1] -= 1;
		}
		else{
			female[l] += 1;
			female[r+1] -= 1;
		}
	}
	for(int i=1; i<D; i++){
		male[i] += male[i-1];
		female[i] += female[i-1];
	}
	int ans = 0;
	for(int i=1; i<=366; i++){
		ans = max(ans,2*min(male[i],female[i]));
	}
	cout << ans << endl;
	return 0;
 
}
