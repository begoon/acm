// BEGIN CUT HERE
// PROBLEM STATEMENT
// A palindrome is a string that is the same whether it is read from left to right or from right to left. Little 
// Dazdraperma likes 
// palindromes a lot. As a birthday gift she received two strings A and B. Now she is curious if there is a 
// way to insert string B into string A so that the resulting string is a palindrome. You agreed to help her and 
// even tell how many different variants of such insertions exist. Two variants are considered different if 
// string B is inserted in different places. Return the number of possible insertion variants.
// 
// 
// For example, let A="aba" and  B="b". You can insert B in 4 different places:
// Before the first letter of A. The result is "baba" and it is not a palindrome.
// After the first letter 'a'. The result is "abba" and it is a palindrome.
// After the letter 'b'. The result is "abba" and it is also a palindrome.
// After the second letter 'a'. The result is "abab" and it is not a palindrome.
// 
// So, the answer for this example is 2.
// 
// DEFINITION
// Class:PalindromesCount
// Method:count
// Parameters:string, string
// Returns:int
// Method signature:int count(string A, string B)
// 
// 
// CONSTRAINTS
// -A and B will each contain between 1 and 50 characters, inclusive.
// -Each character of A and B will be a lowercase letter ('a'-'z').
// 
// 
// EXAMPLES
// 
// 0)
// "aba"
// "b"
// 
// Returns: 2
// 
// The example from the problem statement.
// 
// 1)
// "aa"
// "a"
// 
// Returns: 3
// 
// Here every possible insertion point gives you a palindrome.
// 
// 2)
// "aca"
// "bb"
// 
// Returns: 0
// 
// No possible solutions.
// 
// 3)
// "abba"
// "abba"
// 
// Returns: 3
// 
// 4)
// "topcoder"
// "coder"
// 
// Returns: 0
// 
// END CUT HERE

#line 73 "problem.cpp"
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

bool is_palindrom(string a) {
  int sz = a.length();
  for (int i = 0; i < sz / 2; ++i)
    if (a[i] != a[sz - i - 1])
      return false;
  return true;
}

class PalindromesCount { 
  public: 
    int count(string A, string B)  { 
      int r = 0;
      for (int i = 0; i < A.length() + 1; ++i) {
        string t = A;
        t.insert(i, B);
        if (is_palindrom(t))
          r += 1;
      }
      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aba"; string Arg1 = "b"; int Arg2 = 2; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "aa"; string Arg1 = "a"; int Arg2 = 3; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "aca"; string Arg1 = "bb"; int Arg2 = 0; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "abba"; string Arg1 = "abba"; int Arg2 = 3; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "topcoder"; string Arg1 = "coder"; int Arg2 = 0; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  PalindromesCount ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
