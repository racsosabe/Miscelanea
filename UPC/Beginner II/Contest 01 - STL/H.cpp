#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int m;
char op[10];

int main(){
	scanf("%d", &n);
	m = 2 * n;
	int ans = 0;
	int nxtval = 1;
	int ordered = 0;
	vector<int> values;
	for(int i = 1; i <= m; i++){
		scanf("%s", op);
		if(op[0] == 'a'){
			int x;
			scanf("%d", &x);
			values.emplace_back(x);
		}
		else{
			if(values.size() <= ordered){
				values.pop_back();
				ordered -= 1;
			}
			else if(values.back() != nxtval){
				values.pop_back();
				ordered = values.size();
				ans += 1;
			}
			else{
				values.pop_back();
			}
			nxtval += 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
