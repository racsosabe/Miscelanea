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
int w[20];
string name;
vector<char> S;

vii parseIntervals(vi &v){
	vii ans(v.size());
	for(int i=0; i<v.size(); i++){
		if(v[i] != -1) ans[i] = mp(v[i], v[i]);
	}
	int L = 0;
	for(int i=0; i<ans.size(); i++){
		if(v[i] == -1){
			ans[i].first = L;
		}
		else{
			L = v[i] + 1;
		}
	}
	int R = 25;
	for(int i=ans.size()-1; i>=0; i--){
		if(v[i] == -1){
			ans[i].second = R;
		}
		else{
			ans[i].first = ans[i].second = v[i];
			R = v[i] - 1;
		}
	}
	return ans;
}

bool backtracking(int pos, int sum, int ranks, vi &avail){
	if(pos == -1){
		return true;
	}
	bool ans = false;
	vii intervals = parseIntervals(avail);
	for(ii a : intervals){
		if(a.first > a.second) return false;
	}
	for(int i=0; i<n and !ans; i++){
		if(ranks & (1<<i)){
			ii last = intervals[i];
			int res = add(w[pos], 10 - add(sum,i,10),10);
			while(res < 26 and !ans){
				if(last.first <= res and res <= last.second){
					avail[i] = res;
					if(backtracking(pos-1, sum + res, ranks ^ (1<<i), avail)){
						S.emplace_back(res + 'a');
						ans = true;
					}
					avail[i] = -1;
				}
				res += 10;
			}
		}
	}
	return ans;
}

int main(){
	int t;
	ri2(t,n);
	while(t--){
		cin >> name;
		for(int i=0; i<n; i++) w[i] = name[i] - '0';
		vi intervals(n);
		for(int i=0; i<n; i++){
			intervals[i] = -1;
		}
		S.clear();
		if(!backtracking(n-1,0,(1<<n)-1,intervals)) puts("-1");
		else{
			for(int i=0; i<S.size(); i++){
				putchar(S[i]);
			}
			putchar('\n');
		}
	}
	return 0;
}
