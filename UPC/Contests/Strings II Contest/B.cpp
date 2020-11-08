#include<bits/stdc++.h>
using namespace::std;

const int SUML = 200000 + 5;
const int E = 26;

int n;
char s[SUML];
char t[SUML];
int nodes[2];
int prefix[SUML];
int suffix[SUML];
int suf[2][SUML];
int frec[2][SUML];
int go[2][SUML][E];

void insert(){
	int len = strlen(s);
	int pos = 0;
	for(int i = 0; i < len; i++){
		int nxt = s[i] - 'a';
		if(go[0][pos][nxt] == 0){
			go[0][pos][nxt] = nodes[0]++;
		}
		pos = go[0][pos][nxt];
	}
	frec[0][pos] += 1;
	pos = 0;
	for(int i = len - 1; i >= 0; i--){
		int nxt = s[i] - 'a';
		if(go[1][pos][nxt] == 0){
			go[1][pos][nxt] = nodes[1]++;
		}
		pos = go[1][pos][nxt];
	}
	frec[1][pos] += 1;
}

void BFS(int id){
	queue<int> Q;
	Q.emplace(0);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		frec[id][u] += frec[id][suf[id][u]];
		for(int i = 0; i < E; i++){
			if(go[id][u][i]){
				int v = go[id][u][i];
				suf[id][v] = u ? go[id][suf[id][u]][i] : 0;
				Q.emplace(v);
			}
			else{
				go[id][u][i] = u ? go[id][suf[id][u]][i] : 0;
			}
		}
	}
}

void buildAutomata(int npat){
	nodes[0] = nodes[1] = 1;
	for(int i = 1; i <= npat; i++){
		scanf("%s", s);
		insert();
	}
	for(int i = 0; i < 2; i++) BFS(i);
}

void preprocess(){
	int len = strlen(t);
	int state = 0;
	for(int i = 0; i < len; i++){
		int nxt = t[i] - 'a';
		state = go[0][state][nxt];
		prefix[i] = frec[0][state];
	}
	state = 0;
	for(int i = len - 1; i >= 0; i--){
		int nxt = t[i] - 'a';
		state = go[1][state][nxt];
		suffix[i] = frec[1][state];
	}
}

long long solve(){
	int len = strlen(t);
	long long ans = 0LL;
	for(int i = 0; i + 1 < len; i++){
		ans += 1LL * prefix[i] * suffix[i + 1];
	}
	return ans;
}

int main(){
	scanf("%s", t);
	scanf("%d", &n);
	buildAutomata(n);
	preprocess();
	long long ans = solve();
	printf("%lld\n", ans);
	return 0;
}
