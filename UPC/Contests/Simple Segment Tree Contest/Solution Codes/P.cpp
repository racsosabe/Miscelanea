#include<bits/stdc++.h>
#define mp make_pair
using namespace::std;

/* Inicial:
 * f(x) = x
 * Luego, en [l,r]
 * f(x) = y
 * (f o g) es asociativa
 *
 * Para todo 1 <= x <= 100 voy a guardar un st que me va dar la funcion final
 * de biyección
 *
 * f(i, x) = y
 *
 * Tranformación en el tiempo i de los valores x.
 *
 *
 * Guardamos la tupla (t, x, y) si es que f(t, x) = y se activa en el rango
 * Guardamos la tupla (t, x, x) si es que f(t, x) = y se desactiva en el rango ->
 * f(t, x) = x
*/

const int N = 200000 + 5;
const int M = 100 + 5;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int n;
int q;
int a[N];
queue<iii> Q[N];
int st[4 * N][M];

void merge(int p, int l, int r){
	for(int i = 1; i <= 100; i++){
		st[p][i] = st[r][st[l][i]];
	}
}

void build(int pos = 1, int l = 0, int r = q - 1){
	if(l == r){
		for(int i = 1; i <= 100; i++){
			st[pos][i] = i;
		}
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	merge(pos, 2 * pos, 2 * pos + 1);
}

void update(int t, int x, int y, int pos = 1, int l = 1, int r = q){
	if(l == r){
		st[pos][x] = y;
		return;
	}
	int mi = (l + r) / 2;
	if(l <= t and t <= mi) update(t, x, y, 2 * pos, l, mi);
	else update(t, x, y, 2 * pos + 1, mi + 1, r);
	merge(pos, 2 * pos, 2 * pos + 1);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &q);
	int l, r, x, y;
	for(int i = 1; i <= q; i++){
		scanf("%d %d %d %d", &l, &r, &x, &y);
		Q[l].emplace(mp(i, mp(x, y)));
		Q[r+1].emplace(mp(i, mp(x, x)));
	}
	build();
	for(int i = 1; i <= n; i++){
		while(!Q[i].empty()){
			iii act = Q[i].front();
			Q[i].pop();
			update(act.first, act.second.first, act.second.second);
		}
		printf("%d%c", st[1][a[i]], " \n"[i == n]);
	}
	return 0;
}
