#include<bits/stdc++.h>
using namespace::std;

const int N = 20+5;

int n, m;
char rows[N];
char cols[N];

int main(){
	scanf("%d %d", &n, &m);
	scanf("%s", rows);
	scanf("%s", cols);
	bool can = (rows[0] != rows[n - 1]) & (cols[0] != cols[m - 1]);
	if(rows[0] == '<'){
		can &= cols[0] != '^';
	}
	else{
		can &= cols[0] != 'v';
	}
	puts(can? "YES" : "NO");
	return 0;
}
