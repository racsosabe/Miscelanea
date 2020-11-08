#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
char s[N];
long long total = 0LL;
stack< pair<int, int> > values;

pair<long long, int> query(int x){
	int cnt = 0;
	long long suma = 0LL;
	while(!values.empty() and values.top().first >= x){
		cnt += values.top().second;
		suma += 1LL * values.top().first * values.top().second;
		values.pop();
	}
	return make_pair(suma, cnt);
}

void insert(int x){
	pair<long long, int> cur = query(x);
	int cnt_geq = cur.second + 1;
	total -= cur.first;
	values.emplace(make_pair(x, cnt_geq));
	total += 1LL * cnt_geq * x;
}

vector<int> suffix_array(){
	vector<int> a(n);
	iota(a.begin(), a.end(), 0);
	sort(a.begin(), a.end(), [&] (int i, int j){
		return s[i] < s[j];		
	});
	vector<int> mapeo(n);
	mapeo[a[0]] = 0;
	for(int i = 1; i < n; i++){
		mapeo[a[i]] = mapeo[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
	}
	int len = 1;
	vector<int> head(n);
	vector<int> new_mapeo(n);
	vector<int> sorted_by_second(n);
	while(len < n){
		for(int i = 0; i < n; i++){
			sorted_by_second[i] = (a[i] - len + n) % n;
		}
		for(int i = n - 1; i >= 0; i--){
			head[mapeo[a[i]]] = i;
		}
		for(int i = 0; i < n; i++){
			int x = sorted_by_second[i];
			a[head[mapeo[x]]++] = x;
		}
		new_mapeo[a[0]] = 0;
		for(int i = 1; i < n; i++){
			if(mapeo[a[i - 1]] != mapeo[a[i]]){
				new_mapeo[a[i]] = new_mapeo[a[i - 1]] + 1;
			}
			else{
				int pre = mapeo[(a[i - 1] + len) % n];
				int cur = mapeo[(a[i] + len) % n];
				new_mapeo[a[i]] = new_mapeo[a[i - 1]] + (pre != cur);
			}
		}
		len <<= 1;
		swap(mapeo, new_mapeo);
	}
	return a;
}

vector<int> lcp_array(vector<int> &a){
	vector<int> rank(n);
	for(int i = 0; i < n; i++){
		rank[a[i]] = i;
	}
	int k = 0;
	vector<int> lcp(n - 1, 0);
	for(int i = 0; i < n; i++){
		if(rank[i] == n - 1){
			k = 0;
			continue;
		}
		int j = a[rank[i] + 1];
		while(i + k < n and j + k < n and s[i + k] == s[j + k]) k += 1;
		lcp[rank[i]] = k;
		if(k > 0) k -= 1;
	}
	return lcp;
}

long long solve(vector<int> &a, vector<int> &lcp){
	long long ans = 0LL;
	int len = n - 1;
	for(int i = 1; i < n; i++){
		ans += len - a[i];
		insert(lcp[i - 1]);
		ans += total;
	}
	return ans;
}

int main(){
	scanf("%s", s);
	n = strlen(s);
	s[n++] = 0;
	vector<int> a = suffix_array();
	vector<int> lcp = lcp_array(a);
	long long ans = solve(a, lcp);
	printf("%lld\n", ans);
	return 0;
}
