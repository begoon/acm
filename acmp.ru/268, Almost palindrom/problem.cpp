#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

/*
 x x x x x  x 1 x x x  x 1 1 2 2
 1 2 3 4 x  0 x 1 x x  0 0 1 1 2
 x 1 2 3 x  x 0 x 1 x  x 0 0 1 1
 x x 1 2 x  x x 0 x 1  x x 0 0 1
 x x x 1 x  x x x 0 x  x x x 0 x

 x x x  x 0 x  x 0 0
 x x x  x x 0  x x 0
 x x x  x x x  x x x

 t = 1: k = 0..  <--¬
 t = 2: k = 1.. <-¬ 1
 t = 3: k = 1..  -1-- <--¬
 t = 4: k = 2.. ---      1
 t = 5: k = 2..    -------

*/

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  
  int N, K;
  string s;
  cin >> N >> K >> s; 

  int r = 0;

  vector<vector<int> > dp(2, vector<int>(N, 0));
  for (int t = 1; t < N; ++t) {
    int p = t & 1;
    int k = t / 2;
    for (int i = 0; i < N - t; ++i) {
      int j = i + t;
      if (s[i] != s[j]) 
        dp[p][k] += 1;
      if (dp[p][k] <= K)
        r += 1;
      // cout << dp[p][k] << " ";
      k += 1;
    }
    // cout << endl;
  }

  cout << r + N << endl;

  return 0;
}
