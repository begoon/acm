// BEGIN CUT HERE
// PROBLEM STATEMENT
// NOTE: This problem statement contains superscripts that may not display properly if viewed outside of the applet.
// Elly loves "div 2" problems! By this she means problems in which she has to divide by two! She notices that some 
// numbers contain prime numbers in themselves! A number X contains another number Y if Y = X / 2k (here and everywhere 
// later in the statement the results of all divisions are rounded down, i.e., integer divisions), for some non-negative 
// integer k.
// She calls all positive integers "prime containers" and defines the size of a prime container as the number of prime 
// numbers contained in that positive integer. For example the size of number 7 is 2, because 7/1 = 7 and 7/2 = 3 are 
// prime; the size of 47 is 5, because 47, 23, 11, 5 and 2 are prime; the size of 959 is 6, since it contains the prime 
// numbers 479, 239, 59, 29, 7 and 3.
// Given a positive int N help Elleonora by finding the number of prime numbers it contains.
// 
// 
// DEFINITION
// Class:PrimeContainers
// Method:containerSize
// Parameters:int
// Returns:int
// Method signature:int containerSize(int N)
// 
// 
// NOTES
// -A prime number is a natural number greater than one that has exactly two distinct natural number divisors: 1 and 
// itself.
// 
// 
// CONSTRAINTS
// -N will be between 1 and 1,000,000, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// 10
// 
// Returns: 2
// 
// The generated sequence is 10, 5, 2, 1. Ten is not a prime, however five and two are.
// 
// 1)
// 42
// 
// Returns: 2
// 
// The Answer to Life, The Universe and Everything is quite poor prime container.
// 
// 2)
// 47
// 
// Returns: 5
// 
// One of the examples in the problem statement.
// 
// 3)
// 959
// 
// Returns: 6
// 
// Another example from the problem statement.
// 
// 4)
// 421337
// 
// Returns: 2
// 
// END CUT HERE

#line 70 "problem.cpp"
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

class PrimeContainers { 
  public: 
    int containerSize(int N)  { 
      vector<bool> is_prime(N + 1, true);
      is_prime[0] = is_prime[1] = false;

      int max = sqrt((double)N + 1);
      for (int i = 2; i <= max; i++) {
        if (!is_prime[i]) continue;

        for (int j = 2*i; j < N + 1; j += i) {
          is_prime[j] = false;
        }
      }

      int r = 0;
      while (N > 0) {
        if (is_prime[N]) r += 1;
        N /= 2;
      }

      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 2; verify_case(0, Arg1, containerSize(Arg0)); }
	void test_case_1() { int Arg0 = 42; int Arg1 = 2; verify_case(1, Arg1, containerSize(Arg0)); }
	void test_case_2() { int Arg0 = 47; int Arg1 = 5; verify_case(2, Arg1, containerSize(Arg0)); }
	void test_case_3() { int Arg0 = 959; int Arg1 = 6; verify_case(3, Arg1, containerSize(Arg0)); }
	void test_case_4() { int Arg0 = 421337; int Arg1 = 2; verify_case(4, Arg1, containerSize(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  PrimeContainers ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
