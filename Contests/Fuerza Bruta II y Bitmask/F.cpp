#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000+5;

int n;
char s[N];

vector< pair<char, int> > initialize(){
	int L = 0, R = 0;
	vector< pair<char, int> > res;
	while(L < n){
		while(R < n and s[L] == s[R]){
			R += 1;
		}
		res.emplace_back(make_pair(s[L], R - L));
		L = R;
	}
	return res;
}

int main(){
	scanf("%s", s);
	n = strlen(s);
	int ans = 0;
	int len = 0;
	vector<char> S;
	vector< pair<char,int> > colors = initialize();
	while(colors.size() > 1){
		vector< pair<char, int> > new_colors;
		int need = n;
		for(int i = 0; i < colors.size(); i++){
			if(i == 0 or i + 1 == colors.size()) need = min(need, colors[i].second);
			else need = min(need, (colors[i].second + 1) / 2);
		}
		ans += need;
		for(int i = 0; i < colors.size(); i++){
			colors[i].second = max(0, colors[i].second - need * (i == 0 or i + 1 == colors.size()? 1 : 2));
		}
		for(int i = 0; i < colors.size(); i++){
			if(colors[i].second == 0) continue;
			if(new_colors.empty()) new_colors.emplace_back(colors[i]);
			else{
				if(new_colors.back().first == colors[i].first) new_colors.back().second += colors[i].second;
				else new_colors.emplace_back(colors[i]);
			}
		}
		swap(new_colors, colors);
	}
	printf("%d\n", ans);
	return 0;
}

