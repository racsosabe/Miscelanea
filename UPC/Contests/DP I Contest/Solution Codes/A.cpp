#include<bits/stdc++.h>
using namespace::std;

const int N = 100+5;

int n, r;
int a[N];
int b[N];

int main(){
	scanf("%d %d", &n, &r);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", a + i, b + i);
	}
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	sort(p.begin(), p.end(), [&] (int i, int j){
		if(b[i] >= 0 and b[j] < 0) return true;
		if(b[i] < 0 and b[j] >= 0) return false;
		if(b[i] < 0){
			return max(a[i], -b[i]) + b[i] > max(a[j], -b[j]) + b[j];
		}
		else{
			return a[i] < a[j];
		}
	});
	for(int i : p){
		if(r >= a[i]){
			r += b[i];
		}
		else{
			puts("NO");
			return 0;
		}
		if(r < 0){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
