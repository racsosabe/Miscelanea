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

const int N = 5;

int n = 4;
int carry[N][N];
char table[N][N];
int dx[] = {1,-1,0,0,0};
int dy[] = {0,0,1,-1,0};

bool can(int mask){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			carry[i][j] = table[i][j] == 'b';
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(mask & (1<<(n * i + j))){
				for(int k = 0; k < 5; k++){
					int vx = i + dx[k];
					int vy = j + dy[k];
					if(0 <= min(vx,vy) and max(vx,vy) < n){
						carry[vx][vy] ^= 1;
					}
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(carry[i][j] != carry[0][0]) return false;
		}
	}
	return true;
}

int main(){
	for(int i=0; i<n; i++){
		scanf("%s",table[i]);
	}
	int ans = n * n + 5;
	for(int mask = 0; mask < 1<<(n*n); mask++){
		if(can(mask)){
			ans = min(ans,(int)__builtin_popcount(mask));
		}
	}
	if(ans > n*n) puts("Impossible");
	else cout << ans << endl;
	return 0;
}
