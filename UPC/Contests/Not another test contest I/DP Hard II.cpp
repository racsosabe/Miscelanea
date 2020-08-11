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

const int N = 1000+5;
const int M = 10000+5;
const int inf = 1<<29;

int n;
int v[N];
int c[N];
int open[N];
int need_before[N];
int close[N];
bool vis[N][M];
int memo[N][M];
bool choice[N][M];

void getBalance(int pos, string &s){
	int sum = 0;
	for(int i=0; i<s.size(); i++){
		if(s[i] == '(') sum += 1;
		else{
			if(sum == 0){
				close[pos] += 1;
			}
			else sum -= 1;
		}
	}
	open[pos] = sum;
}

int DP(int pos, int balance){
	if(pos == n){
		return balance == 0? 0 : -inf;
	}
	if(vis[pos][balance]) return memo[pos][balance];
	int ans = DP(pos+1,balance);
	if(balance - close[v[pos]] >= 0){
		int cand = c[v[pos]] + DP(pos+1,balance - close[v[pos]] + open[v[pos]]);
		if(ans < cand){
			ans = cand;
			choice[pos][balance] = 1;
		}
	}
	vis[pos][balance] = true;
	return memo[pos][balance] = ans;
}

bool isGood(int x){
	return open[x] - close[x] >= 0;
}

bool isBad(int x){
	return !isGood(x);
}

int main(){
	ri(n);
	getchar();
	string s;
	for(int i=0; i<n; i++){
		getline(cin,s);
		getBalance(i,s);
		c[i] = s.size();
	}
	for(int i=0; i<n; i++) v[i] = i;
	sort(v, v+n, [&](int i, int j){
		if(isGood(i) and isBad(j)) return true;
		if(isBad(i) and isGood(j)) return false;
		if(isGood(i)){
			return close[i] < close[j];
		}
		return open[i] > open[j];
	});
	int L = DP(0,0);
	vi ans;
	int b = 0;
	for(int i=0; i<n; i++){
		if(choice[i][b]){
			ans.emplace_back(v[i] + 1);
			b -= close[v[i]];
			b += open[v[i]];
		}
	}
	printf("%d %d\n",L,(int)ans.size());
	if(ans.empty()) puts("");
	for(int i=0; i<ans.size(); i++){
		printf("%d%c",ans[i]," \n"[i + 1 == ans.size()]);
	}
	return 0;
}
