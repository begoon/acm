// BEGIN CUT HERE
// PROBLEM STATEMENT
// Elly is great fan of consistency. She would like to have order in even the simplest things in life – like listening to 
// music.
// 
// She has chosen several songs from which she wants to compose a playlist. The names of these songs are given in vector 
// <string> songs, where each element is the name of a single song. Each name is unique and consists of at least three 
// lowercase Latin letters.
// 
// A playlist is a sequence containing exactly K song names from songs. Each song from songs can be included zero, one or 
// more times into a playlist. For each song in her playlist (except the last one), Elly wants the transition from this 
// song to the next one in the playlist to be smooth. She calls transition from one song to another smooth if the 
// substring formed by the first three letters of the name of the new song is the same as the substring formed by the 
// last three letters from the name of the previous song. For example valid smooth transitions are from "xxxabc" to 
// "abcyyy", from "entersandman" to "maneater", or from "heavensalie" to "liebe". On the other hand invalid transitions 
// are from "yyydefg" to "defgyyy", from "toxicity" to "citylights", from "fadetoblack" to "breakingthehabit", from 
// "hello" to "lol" or from "abbccddd" to "bcda".
// 
// Elly wonders how many different playlists with exactly K songs she can make from the given songs, while respecting her 
// wish to have smooth transition between each two consecutive ones. Since this number can be quite large, return its 
// remainder when divided by 1,000,000,007. Two playlists are considered different if there is an index i such that the i-
// th songs in these playlists are different.
// 
// DEFINITION
// Class:EllysPlaylists
// Method:countPlaylists
// Parameters:vector <string>, int
// Returns:int
// Method signature:int countPlaylists(vector <string> songs, int K)
// 
// 
// CONSTRAINTS
// -K will be between 1 and 1000, inclusive.
// -songs will contain between 1 and 50 elements, inclusive.
// -Each element of songs will contain between 3 and 20 characters, inclusive.
// -Each element of songs will consist of lowercase Latin letters ('a'-'z') only.
// -All elements of songs will be distinct.
// 
// 
// EXAMPLES
// 
// 0)
// { "abcxxx", "xxxabc", "entersandman", "toxicity", "maneater", "heavensalie",
//   "liebe", "citylights", "fadetoblack", "breakingthehabit", "yyydefg", "defgyyy" }
// 2
// 
// Returns: 5
// 
// The possible pairs are {"abcxxx", "xxxabc"}, {"xxxabc", "abcxxx"}, {"entersandman", "maneater"}, {"heavensalie", 
// "liebe"}, and {"defgyyy", "yyydefg"}.
// Note that the order of the songs is important.
// 
// 1)
// { "aaaaaa", "aaabcd", "bcdaaa" }
// 4
// 
// Returns: 13
// 
// One song can be used more than once in a playlist.
// 
// 2)
// { "aaa", "aaaa", "aaaaa" }
// 3
// 
// Returns: 27
// 
// Aaaaaaa...
// 
// 3)
// { "elly", "looks", "lovely" }
// 1
// 
// Returns: 3
// 
// Each song is a valid playlist.
// 
// 4)
// { "life", "universe", "everything" }
// 42
// 
// Returns: 0
// 
// No valid sequence of 42 songs exists.
// 
// 5)
// { "aaaaaaaaa", "aaabbbaaa", "aaacccaaa", "aaadddaaa", "aaaeeeaaa", "aaafffaaa" }
// 12
// 
// Returns: 176782322
// 
// The answer can be quite large, so don't forget to return only its remainder.
// 
// END CUT HERE

#line 96 "problem.cpp"
#include <string>
#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
using namespace std;

class EllysPlaylists { 
  public: 
    int countPlaylists(vector <string> songs, int K)  { 
      int N = songs.size();

      vector<vector<int> > a(N, vector<int>(N, false));
      for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
          string t = songs[i].substr(songs[i].length() - 3, 3);
          string h = songs[j].substr(0, 3);
          a[i][j] = t == h;
        }

      vector<vector<int> > dp(K + 1, vector<int>(N, 0));
      for (int i = 0; i < N; ++i) dp[1][i] = 1;
      for (int k = 2; k <= K; ++k)
        for (int i = 0; i < N; ++i)
          for (int j = 0; j < N; ++j)
            if (a[j][i])
              dp[k][i] = (dp[k][i] + dp[k-1][j]) % 1000000007;

      int r = 0;
      for (int i = 0; i < N; ++i)
        r = (r + dp[K][i]) % 1000000007;

      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "abcxxx", "xxxabc", "entersandman", "toxicity", "maneater", "heavensalie",
  "liebe", "citylights", "fadetoblack", "breakingthehabit", "yyydefg", "defgyyy" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 5; verify_case(0, Arg2, countPlaylists(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = { "aaaaaa", "aaabcd", "bcdaaa" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 13; verify_case(1, Arg2, countPlaylists(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = { "aaa", "aaaa", "aaaaa" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 27; verify_case(2, Arg2, countPlaylists(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = { "elly", "looks", "lovely" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; verify_case(3, Arg2, countPlaylists(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = { "life", "universe", "everything" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 42; int Arg2 = 0; verify_case(4, Arg2, countPlaylists(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = { "aaaaaaaaa", "aaabbbaaa", "aaacccaaa", "aaadddaaa", "aaaeeeaaa", "aaafffaaa" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 176782322; verify_case(5, Arg2, countPlaylists(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  EllysPlaylists ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
