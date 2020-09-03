#include<bits/stdc++.h>
using namespace::std;
 
const int MAX_DEPTH = 11;
const int MAX_ROW = 1030;
const int MAX_COL = 2050;
 
bool done[MAX_DEPTH];
char tabla[MAX_DEPTH][MAX_ROW][MAX_COL];
 
void f(int depth, int n, int x, int y){
	if(n == 1){
		tabla[depth][x][y] = '/';
		tabla[depth][x][y + 1] = '\\';
		tabla[depth][x + 1][y - 1] = '/';
		tabla[depth][x + 1][y + 2] = '\\';
		tabla[depth][x + 1][y] = tabla[depth][x + 1][y + 1] = '_';
	}
	else{
		int dy = 1 << (n - 1);
		int dx = 1 << (n - 1);
		f(depth, n - 1, x + dx, y - dy);
		f(depth, n - 1, x + dx, y + dy);
		f(depth, n - 1, x, y);
	}
}
 
int main(){
	int n;
	while(scanf("%d", &n) == 1 and n){
		if(done[n]){
			for(int i = 0; i < 1 << n; i++){
				printf("%s\n",tabla[n][i]);
			}
		}
		else{
			memset(tabla[n], ' ', sizeof tabla[n]);
			f(n, n, 0, (1 << n) - 1);
			for(int i = 0; i < 1 << n; i++){
				int pos = MAX_COL - 1;
				while(tabla[n][i][pos]==' '){
					pos--;
				}
				tabla[n][i][pos + 1] = '\0';
			}
			for(int i = 0; i < 1 << n; i++) printf("%s\n", tabla[n][i]);
			done[n] = true;
		}
		puts("");
	}
	return 0;
}
