#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

char s[N];
vector<char> v;

int main(){
	scanf("%s", s);
	int len = 0;
	for(int i = 0; s[i]; i++){
		v.emplace_back(s[i]);
		len += 1;
		while(len >= 2 and v[len - 2] == v[len - 1]){
			v.pop_back();
			v.pop_back();
			len -= 2;
		}
	}
	for(int i = 0; i < len; i++){
		putchar(v[i]);
	}
	putchar('\n');
	return 0;
}
