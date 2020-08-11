#include<bits/stdc++.h>
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ri(x) scanf("%d",&(x))
#define ri2(x,y) scanf("%d %d",&(x),&(y))
#define ri3(x,y,z) scanf("%d %d %d",&(x),&(y),&(z))
#define rll(x) scanf("%lld",&(x))
#define rll2(x,y) scanf("%lld %lld",&(x),&(y))
#define rll3(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z))
#define gc(x) ((x) = getchar())
using namespace::std;

const long double PI = acos(-1);
const long long MOD = 1000000000 +7;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> tll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<tll> vtll;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ii> sii;
typedef set<iii> siii;

ll gcd(ll a, ll b){ return b==0?a:gcd(b,a%b);}

ll add(ll a, ll b, ll m = MOD){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	if(a < 0) a += m;
	if(b < 0) b += m;
	ll res = a+b;
	if(res >= m or res <= -m) res %= m;
	if(res < 0) res += m;
	return res;
}

ll mul(ll a, ll b, ll m = MOD){
	if(a >= m) a %= m;
	if(b >= m) b %= m;
	if(a < 0) a += m;
	if(b < 0) b += m;
	ll res = a*b;
	if(res >= m or res <= -m) res %= m;
	if(res < 0) res += m;
	return res;
}

ll pow_mod(ll a, ll b, ll m = MOD){
	ll res = 1LL;
	a = a%m;
	while(b){
		if(b&1) res = mul(res,a,m);
		b >>= 1;
		a = mul(a,a,m);
	}
	return res;
}

ll fastexp(ll a, ll b){
	ll res = 1LL;
	while(b){
		if(b&1) res = res*a;
		b >>= 1;
		a *= a;
	}
	return res;
}

int gcdExtendido(int a, int b, int *x, int *y){
	if(a == 0){
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtendido(b%a,a,&x1,&y1);
	
	*x = y1-(b/a)*x1;
	*y = x1;
	return gcd;
}

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/

const int N = 200000+5;

int n;
int x;
int y;
vi G[N];
int deg[N];
bool vis[N][5];
int memo[N][5];

int DP(int u, int uses, int p = -1){
	if(vis[u][uses]) return memo[u][uses];
	int res = 0;
	if(uses){
		vector<int> bests(uses, - 2 * n);
		for(int v : G[u]){
			if(v == p) continue;
			int aporte = max({DP(v, 0, u), DP(v, 1, u), DP(v, 2, u)});
			res += aporte;
			int change = max({DP(v, 0, u), DP(v, 1, u)}) - aporte;
			if(bests[uses-1] < change){
				bests[uses-1] = change;
			}
			if(uses == 2 and bests[0] < bests[1]) swap(bests[0], bests[1]);
		}
		res += uses;
		for(auto x : bests) res += x;
	}
	else{
		for(int v : G[u]){
			if(v == p) continue;
			res += max({DP(v, 0, u), DP(v, 1, u), DP(v, 2, u)});
		}
	}
	vis[u][uses] = true;
	return memo[u][uses] = res;
}

int main(){
	ri3(n, x, y);
	for(int i=1; i<n; i++){
		int u, v;
		ri2(u, v);
		deg[u] += 1;
		deg[v] += 1;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	ll ans;
	if(x > y){
		ans = 1LL * y * (n - 1);
		if(*max_element(deg + 1, deg + 1 + n) == n-1){
			ans += x - y;
		}
	}
	else{
		int max_edges_in_tree = max({DP(1, 0), DP(1, 1), DP(1, 2)});
		ans = 1LL * x * max_edges_in_tree + 1LL * y * (n - 1 - max_edges_in_tree);
	}
	printf("%lld\n", ans);
	return 0;
}
