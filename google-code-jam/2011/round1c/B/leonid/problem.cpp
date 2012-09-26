#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i++)

void openfiles()
{
#ifndef ONLINE_JUDGE
	string file = "B-small-practice";
	//string file = "B-large";
	//freopen("test.in", "rt", stdin);
	freopen((file + ".in").c_str(),"rt",stdin);
	freopen((file + ".out").c_str(),"wt",stdout);
#endif
}

void solve(int test)
{
	int L, n, C; long long t; scanf("%d %lld %d %d ", &L, &t, &n, &C);
	vector<int> v(n);
	vector<int> a(C);
	for (int i = 0; i < C; i++) scanf("%d ", &a[i]);
	for (int i = 0; i < n; i++) v[i] = a[i % C];

	//for (int i = 0; i < n; i++)
	//	cout << v[i] << " ";
	//cout << endl;
	long long sum = 0;
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		if (sum + v[i] * 2 >= t) {
			int x = (sum + 2 * v[i] - t) / 2;
			nums.push_back(x);
			for (int j = i + 1; j < n; j++) {
				nums.push_back(v[j]);
			}
			break;
		}
		sum += v[i] * 2;
	}
	sort(nums.begin(), nums.end(), greater<int>());
	//for (int i = 0; i < nums.size(); i++)
	//	cout << nums[i] << " ";
	//cout << endl;
	long long total = 0;
	for (int i = 0; i < n; i++) {
		total += v[i];
	}
	long long fast = 0;
	for (int i = 0; i < min((int)nums.size(), L); i++) {
		fast += nums[i];
	}

	long long time = fast + (total - fast) * 2;
	printf("Case #%d: %lld\n", test, time);
}

int main()
{
	openfiles();
	int n; scanf("%d ",&n); REP(i,n) solve(i + 1);
	
	return 0;
}
