#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int L[N];
int R[N];
int ans[N];

void solve(){
	for(int i = 1; i <= n; i++) ans[i] = 0;
	int time = 0;
	for(int i = 1; i <= n; i++){
		time = max(time, L[i]);
		if(time > R[i]) continue;
		ans[i] = time;
		time += 1;
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d %d", &L[i] ,&R[i]);
		}
		solve();
		for(int i = 1; i <= n; i++){
			printf("%d%c", ans[i], " \n"[i == n]);
		}
	}
	return 0;
}
