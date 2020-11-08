#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int SUML = 200 + 5;
const int K = 500 + 5;
const int E = 20 + 5;

int n;
int m;
int k;
int nodes;
int sum[SUML];
int suf[SUML];
vector<int> a;
int go[SUML][E];
bool vis[SUML][SUML][K][2][2];
int memo[SUML][SUML][K][2][2];

vector<int> read(){
	int l;
	scanf("%d", &l);
	vector<int> v;
	for(int i = 0; i < l; i++){
		int x;
		scanf("%d", &x);
		v.emplace_back(x);
	}
	return v;
}

void insert(vector<int> &v, int w){
	int pos = 0;
	for(int nxt : v){
		if(go[pos][nxt] == 0){
			go[pos][nxt] = nodes++;
		}
		pos = go[pos][nxt];
	}
	sum[pos] += w;
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		sum[u] += sum[suf[u]];
		for(int i = 0; i < m; i++){
			if(go[u][i]){
				int v = go[u][i];
				suf[v] = u ? go[suf[u]][i] : 0;
				Q.emplace(v);
			}
			else{
				go[u][i] = u ? go[suf[u]][i] : 0;
			}
		}
	}
}

void buildAutomaton(int npat){
	nodes = 1;
	for(int i = 1; i <= npat; i++){
		int w;
		vector<int> v = read();
		scanf("%d", &w);
		insert(v, w);
	}
	BFS(0);
}

void takeOne(vector<int> &v){
	reverse(v.begin(), v.end());
	v[0] -= 1;
	for(int i = 0; i + 1 < v.size(); i++){
		if(v[i] < 0){
			v[i] += m;
			v[i + 1] -= 1;
		}
	}
	while(v.size() > 1 and v.back() == 0) v.pop_back();
	reverse(v.begin(), v.end());
}

int solve(){
	memset(vis, 0, sizeof vis);
	memset(memo, 0, sizeof memo);
	queue<int> Q;
	Q.emplace(0);
	Q.emplace(0);
	Q.emplace(0);
	Q.emplace(0);
	Q.emplace(0);
	vis[0][0][0][0][0] = true;
	memo[0][0][0][0][0] = 1;
	while(!Q.empty()){
		int pos = Q.front(); Q.pop();
		int state = Q.front(); Q.pop();
		int value = Q.front(); Q.pop();
		int menor = Q.front(); Q.pop();
		int valid = Q.front(); Q.pop();
		int limit = menor ? m - 1 : a[pos];
		if(pos == a.size()) continue;
		for(int d = 0; d <= limit; d++){
			int nvalid = valid | (d > 0);
			int nstate = nvalid ? go[state][d] : 0;
			int nvalue = nvalid ? value + sum[nstate] : 0;
			int nmenor = menor | (d < a[pos]);
			if(nvalue > k) continue;
			if(not vis[pos + 1][nstate][nvalue][nmenor][nvalid]){
				Q.emplace(pos + 1);
				Q.emplace(nstate);
				Q.emplace(nvalue);
				Q.emplace(nmenor);
				Q.emplace(nvalid);
				vis[pos + 1][nstate][nvalue][nmenor][nvalid] = true;
			}
			memo[pos + 1][nstate][nvalue][nmenor][nvalid] += memo[pos][state][value][menor][valid];
			if(memo[pos + 1][nstate][nvalue][nmenor][nvalid] >= MOD) memo[pos + 1][nstate][nvalue][nmenor][nvalid] -= MOD;
		}
	}
	int ans = 0;
	for(int state = 0; state < nodes; state++){
		for(int value = 0; value <= k; value++){
			for(int b = 0; b < 2; b++){
				ans += memo[a.size()][state][value][b][1];
				if(ans >= MOD) ans -= MOD;
			}
		}
	}
	return ans;
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	vector<int> L = read();
	vector<int> R = read();
	buildAutomaton(n);
	a = R;
	int ans = solve();
	takeOne(L);
	a = L;
	ans = (ans + MOD - solve()) % MOD;
	printf("%d\n", ans);
	return 0;
}
