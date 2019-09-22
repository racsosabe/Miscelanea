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
 
const int N = 100000+5;
 
int n, m;
int q;
ll c[N];
ll ft[N];
iii lectures[N];
 
bool comp(iii a, iii b){
	return a.second.first< b.second.first;
}
 
void update(int pos, ll val){
	pos++;
	while(pos <= n+1){
		ft[pos] = max(ft[pos],val);
		pos += (-pos)&pos;
	}
}
 
ll query(int pos){
	pos++;
	ll res = 0;
	while(pos > 0){
		res = max(res,ft[pos]);
		pos &= pos-1;
	}
	return res;
}
 
int main(){
	ri3(n,m,q);
	for(int i=1; i<=m; i++) rll(c[i]);
	for(int i=0; i<q; i++){
		ri3(lectures[i].second.first,lectures[i].second.second,lectures[i].first);
	}
	sort(lectures,lectures+q,comp);
	ll ans = 0LL;
	for(int i=0; i<q; i++){
		int L = lectures[i].second.first;
		int R = lectures[i].second.second;
		ll act = query(L) + c[lectures[i].first];
		update(R,act);
		ans = max(ans,act);
	}
	cout << ans << endl;
	return 0;
}
