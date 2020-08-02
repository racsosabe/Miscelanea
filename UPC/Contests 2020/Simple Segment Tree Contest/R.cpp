#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan
 
	Idea:
 
	- Beautiful data structures problem.
 
	- Explanation based on the official editorial.
 
	- First of all, both dimensions (X and Y) are independent, so we must focus on
	  
	  a strategy to solve a one-dimensional version of the problem of crossing the 
 
	  axis.
 
	- We will focus on prefix sums, since we will care about each i from 1 to n - 1
 
	  that holds prefix[i] * prefix[i + 1] < 0, thus we can reduce our problem to
 
	  counting all the pairs (i, i + 1) such that
 
	  min(prefix[i], prefix[i+1]) < 0 and max(prefix[i], prefix[i+1]) > 0.
 
	  Note: We don't care about 0s since we begin at 1 and all the x_i and y_i are even
 
	- Let's notice that we can count the pairs by mantaining two structures: one 
 
	  for min(prefix[i], prefix[i+1]), say L, and other for max(prefix[i], prefix[i+1]),
	  
	  say H.
 
	  
	  The number of such pairs is:
 
	  (Number of negative elements in L) - (Number of negative elements in H).
 
	  The first one because we need the minimum to be negative and the second one 
 
	  because we need the maximum to be positive (it must not be negative).
 
	- The cursor part is important, since we will always manipulate a suffix of the elements.
 
	  Thus, we can consider the sums of the suffix from the cursor to n and the prefix
 
	  that ends in the previous position as two separate values.
 
	- With the former observation, we can model the problem for a complete array (since
	
	  we always mantain a suffix), so we need to be able to do the following:
 
	  * Add a value x to all the elements in the structure
	  * Count the number of negative values in the structure
	  * Remove the first element
	  * Add an element x in the front of the structure
	
	- We can actually do all the previous operations using a stack and a multiset
 
	  We can use a value D that will represent that each value X in the structure
 
	  is actually (X + D).
 
	  * We just add x to D.
	  * We count the number of elements less than -D (since X + D < 0 -> X < -D)
	  * Pop the top of the stack and remove that value of the multiset
	  * Add the element x - D to both the stack and the multiset.
	 
	  Since std::multiset can't count efficiently, one can use an STL PBDS or any
 
	  data structure that can achieve a logarithmic complexity (or log^2).
 
	  In this code I use Dynamic Segment Tree, which is log(MAX - MIN) per query and update.
	
	- Now, we can mantain the value P as the sum for the prefix before the cursor and 
 
	  each query we can just add the sums for the structures (for both axis).
 
	- So, we are just left with knowing what to do for each query:
 
	  * 'B': Add the pair (cursor-1, cursor) to the structures L, H (for each dimesion)
	         and move the cursor 1 to the left. This must be done only if cursor > 1
	  * 'F': Remove the pair (cursor, cursor + 1) from the structures L, H (for each dimension)
	  
	         and move the cursor 1 to the right. This must be done only if cursor < n
	
	  * 'C nx ny': Add the difference between new value and last value to the structures
 
	         and check if the pair (cursor - 1, cursor) affects the value of P.
 
	  * 'Q': Print P + (Count of pairs for dimension X) + (Count of pairs for dimension Y)
	
	- We can use a Fenwick Tree to simulate the prefix sums variation.
 
	- Complexity: O(m(log(MAX - MIN) + logn)), can be optimized to O(mlogn) expected using treap.
 
*/
 
struct DSegTree{
	int xmin;
	int xmax;
	int nodes;
	vector<int> st, L, R;
 
	DSegTree(){
		xmin = -500 * 100000 - 5;
		xmax = 500 * 100000 + 5;
		nodes = 0;
		st.clear();
		L.clear();
		R.clear();
		addNode();
	}
	
	void addNode(){
		st.emplace_back(0);
		L.emplace_back(-1);
		R.emplace_back(-1);
		nodes += 1;
	}
 
	void update(int x, int y, int pos, int l, int r){
		if(l == r){
			st[pos] += y;
			return;
		}
		int mi = l + (r - l) / 2;
		if(l <= x and x <= mi){
			if(L[pos] == -1){
				L[pos] = nodes;
				addNode();
			}
			update(x, y, L[pos], l, mi);
		}
		else{
			if(R[pos] == -1){
				R[pos] = nodes;
				addNode();
			}
			update(x, y, R[pos], mi+1, r);
		}
		st[pos] = (L[pos] >= 0? st[L[pos]] : 0) + (R[pos] >= 0? st[R[pos]] : 0);
	}
 
	int query(int x, int y, int pos, int l, int r){
		if(y < l or r < x or x > y or pos == -1) return 0;
		if(x <= l and r <= y) return st[pos];
		int mi = l + (r - l) / 2;
		return query(x, y, L[pos], l, mi) + query(x, y, R[pos], mi+1, r);
	}
 
	int query(int y){
		return query(xmin, y, 0, xmin, xmax);
	}
 
	void update(int x, int y){
		update(x, y, 0, xmin, xmax);
	}
};
 
struct Dim{
	int D;
	DSegTree S;
	stack<int> P;
 
	Dim(){
		D = 0;
	};
 
	void init(vector<int> X){
		for(int i = X.size() - 1; i >= 0; i--){
			P.emplace(X[i]);
			S.update(X[i], 1);
		}
	}
 
	int pop(){
		int val = P.top();
		P.pop();
		S.update(val, -1);
		return val;
	}
 
	void push(int val){
		P.emplace(val - D);
		S.update(val - D, 1);
	}
 
	void updateD(int val){
		D += val;
	}
 
	int query(){
		return S.query(-D-1);
	}
};
 
const int N = 100000+5;
 
int n, m;
int P = 0;
Dim Lx, Hx;
Dim Ly, Hy;
int ft[3][N];
int cursor = 1;
int x[N], y[N];
 
void update(int id, int pos, int val){
	pos++;
	while(pos <= n + 1){
		ft[id][pos] += val;
		pos += (-pos) & pos;
	}
}
 
int getSum(int id, int pos){
	pos++;
	int res = 0;
	while(pos > 0){
		res += ft[id][pos];
		pos &= pos-1;
	}
	return res;
}
 
void change(int i, int signo = 1){
	int s_i = getSum(0, i);
	int s_ip = getSum(0, i + 1);
	if(min(s_i, s_ip) < 0 and max(s_i, s_ip) > 0){
		P += signo;
	}
	s_i = getSum(1, i);
	s_ip = getSum(1, i + 1);
	if(min(s_i, s_ip) < 0 and max(s_i, s_ip) > 0){
		P += signo;
	}
}
 
void init(){
	for(int i = 0; i <= n; i++){
		update(0, i, x[i]);
		update(1, i, y[i]);
	}
	vector<int> lx;
	vector<int> hx;
	for(int i = 1; i + 1 <= n; i++){
		int s_i = getSum(0, i);
		int s_ip = getSum(0, i + 1);
		lx.emplace_back(min(s_i, s_ip));
		hx.emplace_back(max(s_i, s_ip));
	}
	Lx.init(lx);
	Hx.init(hx);
	vector<int> ly;
	vector<int> hy;
	for(int i = 1; i + 1 <= n; i++){
		int s_i = getSum(1, i);
		int s_ip = getSum(1, i + 1);
		ly.emplace_back(min(s_i, s_ip));
		hy.emplace_back(max(s_i, s_ip));
	}
	Ly.init(ly);
	Hy.init(hy);
	change(0, 1);
}
 
void moveRight(){
	if(cursor + 1 <= n){
		change(cursor, 1);
		Lx.pop();
		Hx.pop();
		Ly.pop();
		Hy.pop();
		cursor += 1;
	}
}
 
void moveLeft(){
	if(cursor - 1 >= 1){
		change(cursor - 1, -1);
		Lx.push(min(getSum(0, cursor), getSum(0, cursor-1)));
		Hx.push(max(getSum(0, cursor), getSum(0, cursor-1)));
		Ly.push(min(getSum(1, cursor), getSum(1, cursor-1)));
		Hy.push(max(getSum(1, cursor), getSum(1, cursor-1)));
		cursor -= 1;
	}
}
 
void modify(int nx, int ny){
	int lastx = x[cursor];
	int lasty = y[cursor];
	change(cursor - 1, -1);
	update(0, cursor, nx - lastx);
	update(1, cursor, ny - lasty);
	change(cursor - 1, 1);
	Lx.updateD(nx - lastx);
	Hx.updateD(nx - lastx);
	Ly.updateD(ny - lasty);
	Hy.updateD(ny - lasty);
	x[cursor] = nx;
	y[cursor] = ny;
}
 
int solve(){
	return P + Lx.query() - Hx.query() + Ly.query() - Hy.query();
}
 
int main(){
	scanf("%d", &n);
	x[0] = y[0] = 1;
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &x[i], &y[i]);
	}
	init();
	scanf("%d", &m);
	int nx, ny;
	while(m--){
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		if(c == 'B'){
			moveLeft();
		}
		else if(c == 'F'){
			moveRight();
		}
		else if(c == 'C'){
			scanf("%d %d", &nx, &ny);
			modify(nx, ny);
		}
		else{
			printf("%d\n", solve());
		}
	}
	return 0;
}
