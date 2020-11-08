#include<bits/stdc++.h>
using namespace::std;

const int SUML = 100000 + 5;
const int E = 26;

int n;
int nodes;
int h[SUML];
int suf[SUML];
string s[SUML];
int go[SUML][E];
int popularity[SUML];
long long best[SUML];

void insert(int npat){
	int pos = 0;
	for(int i = 0; i < s[npat].size(); i++){
		int nxt = s[npat][i] - 'a';
		if(go[pos][nxt] == 0){
			h[nodes] = h[pos] + 1;
			go[pos][nxt] = nodes++;
		}
		pos = go[pos][nxt];
		popularity[pos] += 1;
	}
}

void BFS(int src){
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front(); Q.pop();
		best[u] = max(best[suf[u]], 1LL * popularity[u] * h[u]);
		for(int i = 0; i < E; i++){
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

void clearAll(){
	for(int i = 0; i < nodes; i++){
		best[i] = 0;
		popularity[i] = 0;
		for(int j = 0; j < E; j++) go[i][j] = 0;
	}
}

int main(){
	int t;
	freopen("exciting.in", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		nodes = 1;
		for(int i = 1; i <= n; i++){
			cin >> s[i];
			insert(i);
		}
		BFS(0);
		long long ans = 0LL;
		for(int i = 1; i <= n; i++){
			int state = 0;
			for(int j = 0; j < s[i].size(); j++){
				int x;
				cin >> x;
				state = go[state][s[i][j] - 'a'];
				ans = max(ans, best[state] * x);
			}
		}
		cout << ans << endl;
		if(t) clearAll();
	}
	return 0;
}
