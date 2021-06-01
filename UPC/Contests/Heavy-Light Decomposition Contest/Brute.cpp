#include<bits/stdc++.h>
using namespace::std;



int main(){
	int best = 1;
	int best_max = 1 << 26;
	vector<int> cnt(4999999);
	for(int i = 5000000; i <= 5000100; i++){
		cnt.emplace_back(0);
		for(int j = 0; j < 1 << 26; j++){
			cnt[j % i] += 1;
		}
		int cur_max = *max_element(cnt.begin(), cnt.end());
		if(cur_max < best_max){
			best = i;
			best_max = cur_max;
		}
		for(int j = 0; j < i; j++) cnt[j] = 0;
	}
	cout << best << " " << best_max << endl;
	return 0;
}
