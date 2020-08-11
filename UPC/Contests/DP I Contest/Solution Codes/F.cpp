#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;
const int E = 256;
const long long inf = 1e18;

int n;
char s[N];
int last[E];
long long k;
long long memo[N][N];

int main(){
    scanf("%d %lld", &n, &k);
    scanf("%s", s);
    memset(last, -1, sizeof last);
    memo[0][0] = 1;
    for(int i = 1; i <= n; i++){
        char c = s[i-1];
        memo[i][0] = memo[i - 1][0];
        for(int l = 1; l <= i; l++){
            memo[i][l] = memo[i - 1][l - 1] + memo[i - 1][l];
            if(last[c] != -1){
                memo[i][l] -= memo[last[c] - 1][l - 1];
            }
            memo[i][l] = min(memo[i][l], inf);
        }
        last[c] = i;
    }
    long long ans = 0LL;
    for(int i = n; i >= 0; i--){
        long long take = min(memo[n][i], k);
        k -= take;
        ans += (n - i) * take;
    }
    if(k > 0) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
