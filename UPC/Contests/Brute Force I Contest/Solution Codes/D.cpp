#include<bits/stdc++.h>
using namespace::std;

int n;
int k1, k2;
deque<int> d1, d2;
set< pair< deque<int>, deque<int> > > vis;

int main(){
	scanf("%d", &n);
	scanf("%d", &k1);
	for(int i = 0; i < k1; i++){
		int x;
		scanf("%d", &x);
		d1.push_back(x);
	}
	scanf("%d", &k2);
	for(int i = 0; i < k2; i++){
		int x;
		scanf("%d", &x);
		d2.push_back(x);
	}
	int turns = 0;
	while(!vis.count(make_pair(d1, d2)) and !d1.empty() and !d2.empty()){
		vis.emplace(make_pair(d1, d2));
		int a1 = d1.front(); d1.pop_front();
		int a2 = d2.front(); d2.pop_front();
		if(a1 > a2){
			d1.push_back(a2);
			d1.push_back(a1);
		}
		else{
			d2.push_back(a1);
			d2.push_back(a2);
		}
		turns += 1;
	}
	if(d1.empty()) printf("%d 2\n", turns);
	else if(d2.empty()) printf("%d 1\n", turns);
	else puts("-1");
	return 0;
}
