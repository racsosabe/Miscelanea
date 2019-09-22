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
const int LOG = 30;
const int M = 1000+5;
 
int len;
int n, C;
int w[N];
int v[N];
vi a, b;
vector<bool> F;
vi nxt;
bool vis[N*LOG][M];
ll memo[N*LOG][M];
 
void getNewValues(){
	len = 0;
	for(int i=0; i<n; i++){
		bool used = false;
		while(v[i] > 0){
			F.emplace_back(false);
			if(!used){
				F.back() = true;
				used = true;
			}
			a.emplace_back(w[i]);
			b.emplace_back(v[i]);
			len++;
			v[i] /= 2;
		}
	}
	int last = len;
	nxt.resize(len);
	for(int i=len-1; i>=0; i--){
		nxt[i] = last;
		if(F[i]) last = i;
	}
}
 
ll DP(int pos, int capacity){
	if(pos == len) return 0LL;
	if(vis[pos][capacity]) return memo[pos][capacity];
	ll ans = DP(nxt[pos],capacity);
	if(capacity >= a[pos]){
		ans = max(ans,b[pos] + DP(pos+1,capacity-a[pos]));
	}
	vis[pos][capacity] = true;
	return memo[pos][capacity] = ans;
}
 
int main(){
	ri2(n,C);
	for(int i=0; i<n; i++){
		ri(w[i]);
	}
	for(int i=0; i<n; i++){
		ri(v[i]);
	}
	getNewValues();
	ll ans = DP(0,C);
	printf("%lld\n",ans);
	return 0;
}
