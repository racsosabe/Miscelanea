#include<bits/stdc++.h>
using namespace::std;

const int B = 10;

int n;
int vor;
int vxor;
int bit[B][3];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < B; i++){
		for(int j = 0; j < 2; j++) bit[i][j] = j;
	}
	for(int i = 1; i <= n; i++){
		char c = getchar();
		while(c != '^' and c != '|' and c != '&') c = getchar();
		int val;
		scanf("%d", &val);
		if(c == '^'){
			for(int b = 0; b < B; b++){
				int act = (val >> b) & 1;
				for(int j = 0; j < 2; j++){
					bit[b][j] ^= act;
				}
			}
		}
		else if(c == '|'){
			for(int b = 0; b < B; b++){
				int act = (val >> b) & 1;
				for(int j = 0; j < 2; j++){
					bit[b][j] |= act;
				}
			}

		}
		else{
			for(int b = 0; b < B; b++){
				int act = (val >> b) & 1;
				for(int j = 0; j < 2; j++){
					bit[b][j] &= act;
				}
			}

		}
	}
	map<int,int> F;
	for(int mask = 0; mask < 4; mask++){
		vector<int> curbit(2, 0);
		curbit[0] = 0;
		curbit[1] = 1;
		int b0 = mask & 1;
		int b1 = (mask >> 1) & 1;
		for(int j = 0; j < 2; j++){
			curbit[j] |= b0;
		}
		for(int j = 0; j < 2; j++){
			curbit[j] ^= b1;
		}
		F[curbit[0] + curbit[1] * 2] = mask;
	}
	assert(F.size() == 4);
	for(int i = 0; i < B; i++){
		int val = F[bit[i][0] + 2 * bit[i][1]];
		vor |= (val & 1) << i;
		vxor |= ((val >> 1) & 1) << i;
	}
	puts("2");
	printf("| %d\n", vor);
	printf("^ %d\n", vxor);
	return 0;
}
