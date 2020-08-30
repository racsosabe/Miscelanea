#include<bits/stdc++.h>
using namespace::std;

const int N = 100000+5;

int n;
char s[N];

int main(){
	scanf("%s", s);
	n = strlen(s);
	sort(s, s + n, greater<char>());
	vector<char> v;
	for(int i = 0; i < n; i++){
		v.emplace_back(s[i]);
		int len = v.size();
		while(len >= 2 and v[len - 2] == v[len - 1] and v[len - 1] < 'z'){
			char x = v[len - 1] + 1;
			v.pop_back();
			v.pop_back();
			v.emplace_back(x);
			len -= 1;
		}
	}
	for(int i = 0; i < v.size(); i++) putchar(v[i]);
	putchar('\n');
	return 0;
}
