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
	string file = "B-large";
	//freopen("test.in", "rt", stdin);
	freopen((file + ".in").c_str(),"rt",stdin);
	freopen((file + ".out").c_str(),"wt",stdout);
#endif
}

void solve(int test)
{
	map<pair<char, char>, char> combine;
	set<pair<char, char> > oppose;
	int n; scanf("%d ", &n);
	for (int i = 0; i < n; i++) {
		char comb[10]; scanf("%s ", comb);
		assert(strlen(comb) == 3);
		combine[make_pair(comb[0], comb[1])] = comb[2];
		combine[make_pair(comb[1], comb[0])] = comb[2];
	}
	scanf("%d ", &n);
	for (int i = 0; i < n; i++) {
		char opp[10]; scanf("%s ", opp);
		assert(strlen(opp) == 2);
		oppose.insert(make_pair(opp[0], opp[1]));
		oppose.insert(make_pair(opp[1], opp[0]));
	}
	char str[1000];
	scanf("%d %s ", &n, str);
	vector<char> lst;
	for (int i = 0; i < n; i++) {
		if (lst.size() <= 0) {
			lst.push_back(str[i]);
			continue;
		}

		int last = lst.size() - 1;
		pair<int, int> p = make_pair(lst[last], str[i]);
		if (combine.find(p) != combine.end()) {
			lst.pop_back();
			lst.push_back(combine[p]);
			continue;
		}

		// find if we can oppose str[i]
		bool opposed = false;
		for (int j = 0; j < lst.size() && !opposed; j++) {
			if (oppose.find(make_pair(lst[j], str[i])) != oppose.end()) {
				opposed = true;
			}
		}
		if (opposed) lst.clear();
		else lst.push_back(str[i]);
	}

	printf("Case #%d: [", test);
	for (int i = 0; i < lst.size(); i++) {
		if (i) printf(", ");
		printf("%c", lst[i]);
	}
	printf("]\n");
}

int main()
{
	openfiles();
	int n; scanf("%d ",&n); REP(i,n) solve(i + 1);
	
	return 0;
}