#include<bits/stdc++.h>
using namespace::std;

int n;
vector<int> lucky;

void init(){
	for(int mask=1; mask < 1<<9; mask++){
		int four = 0;
		int seven = 0;
		int carry = mask;
		while(carry){
			if(carry & 1){
				four = 10 * four + 7;
				seven = 10 * seven + 4;
			}
			else{
				four = 10 * four + 4;
				seven = 10 * seven + 7;
			}
			carry >>= 1;
		}
		lucky.emplace_back(four);
		lucky.emplace_back(seven);
	}
	sort(lucky.begin(), lucky.end());
}

int main(){
	init();
	cin >> n;
	int pos = 0;
	while(lucky[pos] != n){
		pos += 1;
	}
	cout << pos + 1 << endl;
	return 0;
}
