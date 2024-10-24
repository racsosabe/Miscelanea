#include <bits/stdc++.h>
using namespace std;


#define mod 998244353ll
#define PI acos(-1.0)
#define set0(ar) memset(ar, 0, sizeof ar)
#define setinf(ar) memset(ar, 126, sizeof ar)

typedef __int128_t LL;

inline constexpr LL bigmod(LL p, LL e, LL M) {
  LL r = 1;
  for (; e > 0; e >>= 1, p = (p * p) % M)
    if (e & 1) r = (r * p) % M;
  return r;
}
inline constexpr LL modinverse(LL a, LL M) { return bigmod(a, M - 2, M); }

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 21;
// Brute force code, only works upto 11.
int brute(int n) {
  int ar[MX+1];
  for(int i = 0; i < n; i++) ar[i] = i;
  int res = 0, res2 = 0;
  do {
    vector<int> vc;
    for(int i = 0; i < n; i++) {
      if(ar[i] == n-1) continue;
      int v = 0;
      for(int j = 0; j < i; j++) if(ar[j] > ar[i]) v++;
      for(int j = i+1; j < n; j++) if(ar[j] > ar[i]) {
        v--;
        res2++;
      }
      vc.push_back(v);
    }
    sort(vc.begin(), vc.end());
    for(int i = 0; i < (n/2); i++) res += vc[i];
  } while(next_permutation(ar, ar + n));
  return res + res2;
}



int dp[1<<MX][MX+1][2];
int cost[1<<MX][MX+1];
int go(int bp, int smaller, bool taken, int c, int n, int v) {
  if(c >= n) {
    if(smaller <= (n/2) && taken) return 1;
    return 0;
  }
  int &ret = dp[bp][smaller][taken];
  if(ret != -1) return ret;
  ret = 0;

  for(int i = 0; i < n; i++) {
    if(bp & (1<<i)) continue;
    if(i == n-1) {
      ret += go(bp | (1<<i), smaller, taken, c+1, n, v);
      continue;
    }
    int val = cost[bp][i];
    if(val > v) ret += go(bp | (1<<i), smaller, taken, c+1, n, v);
    else if(val < v) ret += go(bp | (1<<i), smaller + 1, taken, c+1, n, v);
    else {
      if(taken) ret += go(bp | (1<<i), smaller, taken, c+1, n, v);
      else {
        ret += go(bp | (1<<i), smaller + 1, false, c+1, n, v);
        ret += go(bp | (1<<i), smaller + 1, true, c+1, n, v);
      }
    }
  }
  return ret;
}

LL ncr[MX+1][MX+1], fact[MX+1];

void print(__int128 x) {
    if(x == 0) return;
    print(x / 10);
    cout << int(x % 10);
}

void solve(int n) {
  fact[0] = 1;
  for(int i = 1; i <= MX; i++) fact[i] = fact[i-1] * (LL)i;
  for(int i = 0; i <= MX; i++) {
    ncr[i][0] = 1;
    for(int j = 1; j <= i; j++) ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
  }

  assert(n % 2 == 1);

  for(int i = 0; i < (1<<n); i++) {
    for(int j = 0; j < n; j++) {
      if(i & (1<<j)) continue;
      for(int k = 0; k < n; k++) {
        if(j == k) continue;
        if((i & (1<<k))) {
          cost[i][j] += k > j;
        } else {
          cost[i][j] -= k > j;
        }
      }
    }
  }
  int sum = 0;
  for(int i = -(n-1); i <= n-1; i++) {
    memset(dp, -1, sizeof dp);
    sum += i*go(0, 0, false, 0, n, i);
  }

  // Count for each permutations the number of pairs (i,j) where i < j and i appears before j.
  LL sum2 = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k <= min(n-1-i, n-1-j); k++) {
        sum2 += ncr[n-1-i][k] * ncr[n-1-j][k] * ncr[i][n-1-j-k] * fact[k] * fact[n-1-j-k] * fact[j] * (LL)k;
      }
    }
  }
  if(sum + sum2) {
    print(sum + sum2);
    cout << endl;
  }
  else cout << 0 << endl;
  //cout << sum+sum2 << " " << brute(n) << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  for(int i = 1; i <= 21; i += 2) {
    solve(i);
  }
}
