#include<bits/stdc++.h>
using namespace::std;

const int N = 200000+5;
const int M = 15;

int n;
bool vis[N][M];
long long memo[N][M];
long long turn[2][4][N];
long long carry[2][4][4];
long long carry2[2][4][4];

void init(int type){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				if(type == 0) carry[i][j][k] = j == 0 and k == 0? 0 : -1e18;
				else carry2[i][j][k] = j == 0 and k == 0? 0 : -1e18;
			}
		}
	}
}

void update(){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				carry[i][j][k] = max(carry[i][j][k], carry2[i][j][k]);
			}
		}
	}

}

void processTurn(int t){
	int k;
	scanf("%d", &k);
	vector<int> c(k), d(k), p(k);
	for(int i = 0; i < k; i++){
		scanf("%d %d", &c[i], &d[i]);
	}
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return d[i] < d[j];
	});
	init(0);
	for(int i = 0; i < k; i++){
		init(1);
		for(int cards = 1; cards <= 3; cards++){
			for(int costo = c[p[i]]; costo <= 3; costo++){
				long long cur_sum = d[p[i]] + carry[0][cards - 1][costo - c[p[i]]];
				if(carry2[0][cards][costo] < cur_sum){
					carry2[0][cards][costo] = cur_sum;
				}
				cur_sum += d[p[i]];
				if(carry2[1][cards][costo] < cur_sum){
					carry2[1][cards][costo] = cur_sum;
				}
			}
		}
		update();
	}
	for(int i = 0; i < 4; i++){
		long long best_sum = -1e18;
		for(int j = 0; j < 4; j++) best_sum = max(best_sum, carry[0][i][j]);
		turn[0][i][t] = best_sum;
		best_sum = -1e18;
		for(int j = 0; j < 4; j++) best_sum = max(best_sum, carry[1][i][j]);
		turn[1][i][t] = best_sum;
	}
}

long long DP(int pos, int cards){
	if(pos == n) return 0LL;
	if(vis[pos][cards]) return memo[pos][cards];
	long long ans = DP(pos + 1, cards);
	for(int i = 1; i <= 3; i++){
		long long cur = cards + i >= 10? turn[1][i][pos] : turn[0][i][pos];
		int nxt_cards = cards + i >= 10? cards + i - 10 : cards + i;
		cur += DP(pos + 1, nxt_cards);
		if(ans < cur) ans = cur;
	}
	vis[pos][cards] = true;
	return memo[pos][cards] = ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		processTurn(i);
	}
	printf("%lld\n", DP(0, 0));
	return 0;
}
