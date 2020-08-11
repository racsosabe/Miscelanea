#include<bits/stdc++.h>
using namespace::std;

const int inf = 2e9;
const int N = 1000+5;

int n;
int v[11];
char s[N][9];
int ac[8][11];
bool can_be_zero[11];

int main(){
	scanf("%d", &n);
	memset(can_be_zero, true, sizeof can_be_zero);
	for(int i=0; i<n; i++){
		scanf("%s", s[i]);
		int len = strlen(s[i]);
		can_be_zero[s[i][0]-'a'] = false;
		for(int j=0; j < len; j++){
			ac[len-1-j][s[i][j]-'a']++;
		}
	}
	for(int i=0; i<10; i++){
		v[i] = i;
	}
	int ans = inf;
	do{
		bool can = true;
		for(int i=0; i<10; i++){
			if(v[i] == 0){
				if(!can_be_zero[i]) can = false;
			}
		}
		if(can){
			int act = 0;
			int p = 1;
			for(int i=0; i<8; i++){
				for(int j=0; j<10; j++){
					act += p* ac[i][j] * v[j];
				}
				p *= 10;
			}
			ans = min(ans,act);
		}
	}while(next_permutation(v, v + 10));
	printf("%d\n", ans);
	return 0;
}

