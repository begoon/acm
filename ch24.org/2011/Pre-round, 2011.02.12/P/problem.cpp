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

const char task = 'P';
void openfiles(int n)
{
	char infile[100], outfile[100];
	sprintf(infile, "%d.in", n);
	sprintf(outfile, "%c%d.out", task, n);

	freopen(infile,"rt",stdin);
	freopen(outfile,"wt",stdout);
}

int magic(int X, int Y) {
	int R = 1;
	while (Y > 0) {
		R = (R * X) % 2011;
		Y = Y - 1;
	}
	return R % 2011;
}

void solve(int test)
{
	long long x, y;
	do {

		long long p = 1, MOD = 2011;
		scanf("%lld %lld ", &x, &y);
		if (!x && !y) return;
		x = x % MOD;

		int yy = y, xx = x;
		for (; y > 0; y >>= 1) {
			if (y & 1) {
				p = (p * x) % MOD;
			}
			x = (x * x) % MOD;
		}
		//if (magic(xx, yy) != p) {
		//	cout << "Failed on " << x << " " << y << endl;
		//	assert(false);
		//}
		printf("%d\n", p);

	} while (true);
}

int main()
{
	int n = 10;
	for (int i = 1; i <= n; i++) {
		openfiles(i);
		solve(i);
	}
	
	return 0;
}