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

int n;
vi v;

ll merge(vi &L, vi &R){
	ll ans = 0LL;
	int posR = 0;
	for(int i=0; i<L.size(); i++){
		while(posR < R.size() and R[posR] <= L[i]){
			posR += 1;
		}
		ans += 1LL * posR * L[i];
	}
	int posL = 0;
	for(int i=0; i<R.size(); i++){
		while(posL < L.size() and L[posL] < R[i]){
			posL += 1;
		}
		ans += 1LL * posL * R[i];
	}
	return ans;
}

ll solve(vi &v){
	if(v.size() == 1) return v[0];
	int len = v.size() / 2;
	vi L(v.begin(), v.begin() + len);
	vi R(v.begin() + len, v.end());
	ll ans = solve(L) + solve(R);
	reverse(all(L));
	for(int i=1; i<L.size(); i++){
		L[i] = max(L[i-1],L[i]);
	}
	for(int i=1; i<R.size(); i++){
		R[i] = max(R[i-1],R[i]);
	}
	ans += merge(L,R);
	return ans;
}

int main(){
	ri(n);
	v.resize(n);
	for(int i=0; i<n; i++) ri(v[i]);
	ll ans = solve(v);
	for(int i=0; i<n; i++) v[i] = -v[i];
	ans += solve(v);
	printf("%lld\n",ans);
	return 0;
}
