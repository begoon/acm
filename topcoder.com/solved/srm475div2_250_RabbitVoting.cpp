// BEGIN CUT HERE
// PROBLEM STATEMENT
// Rabbits often feel lonely, so one group of rabbits decided to get together 
// and hold a beauty contest to determine who among them has the most beautiful ears. 
// The rules are as follows. 
// Each rabbit submits one vote. 
// If a rabbit votes for himself/herself, that vote is considered invalid and thrown away. 
// In the end, the rabbit who receives the most valid votes is the winner. 
// 
// You are given a vector <string> names and a vector <string> votes. 
// The i-th rabbit is named names[i], and he/she voted for the rabbit named votes[i]. 
// All rabbits have distinct names. 
// Return the name of the rabbit who received the most valid votes. 
// If there is a tie for most votes, return an empty string instead. 
// 
// 
// 
// DEFINITION
// Class:RabbitVoting
// Method:getWinner
// Parameters:vector <string>, vector <string>
// Returns:string
// Method signature:string getWinner(vector <string> names, vector <string> votes)
// 
// 
// NOTES
// -Rabbit names are case-sensitive. See example 4 for clarification.
// 
// 
// CONSTRAINTS
// -names will contain between 2 and 50 elements, inclusive. 
// -Each element of names will contain between 1 and 50 characters, inclusive. 
// -Each character in names will be a letter ('A'-'Z', 'a'-'z').
// -All elements of names will be distinct. 
// -votes will contain the same number of elements as names. 
// -Each element of votes will be the same as one of the elements of names. 
// 
// 
// EXAMPLES
// 
// 0)
// { "Alice", "Bill", "Carol", "Dick" }
// { "Bill", "Dick", "Alice", "Alice" }
// 
// Returns: "Alice"
// 
// 2 votes for Alice, 1 for Bill, 0 for Carol, and 1 for Dick. Alice got the most. 
// 
// 
// 1)
// { "Alice", "Bill", "Carol", "Dick" }
// { "Carol", "Carol", "Bill", "Bill" }
// 
// Returns: ""
// 
// Bill and Carol are tied with 2 votes each.
// 
// 2)
// { "Alice", "Bill", "Carol", "Dick" }
// { "Alice", "Alice", "Bill", "Bill" }
// 
// Returns: "Bill"
// 
// Alice's vote for herself is invalid. 1 valid vote for Alice, 2 for Bill.
// 
// 3)
// { "Alice", "Bill" }
// { "Alice", "Bill" }
// 
// Returns: ""
// 
// All votes are invalid. 
// 
// 
// 4)
// { "WhiteRabbit", "whiterabbit", "whiteRabbit", "Whiterabbit" }
// { "whiteRabbit", "whiteRabbit", "whiteRabbit", "WhiteRabbit" }
// 
// Returns: "whiteRabbit"
// 
// These four are different names. 
// 
// 
// END CUT HERE

#line 87 "problem.cpp"
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
#include <map>
#include <cmath>
using namespace std;

class RabbitVoting { 
  public: 
    string getWinner(vector <string> names, vector <string> votes)  { 
      map<string, int> r;
      int m = 0;
      string winner;
      for (int i = 0; i < names.size(); ++i) {
        if (names[i] == votes[i]) continue;
        int t = r[votes[i]];
        t += 1;
        r[votes[i]] = t;
        if (t > m) {
          m = t;
          winner = votes[i];
        }
      }
      int c = 0;
      for (map<string, int>::iterator i = r.begin(); i != r.end(); ++i) {
        if (i->second == m)
          c += 1;
      }
      if (c > 1)
        return "";
      return winner;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = { "Alice", "Bill", "Carol", "Dick" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "Bill", "Dick", "Alice", "Alice" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Alice"; verify_case(0, Arg2, getWinner(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = { "Alice", "Bill", "Carol", "Dick" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "Carol", "Carol", "Bill", "Bill" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = ""; verify_case(1, Arg2, getWinner(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = { "Alice", "Bill", "Carol", "Dick" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "Alice", "Alice", "Bill", "Bill" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Bill"; verify_case(2, Arg2, getWinner(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = { "Alice", "Bill" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "Alice", "Bill" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = ""; verify_case(3, Arg2, getWinner(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = { "WhiteRabbit", "whiterabbit", "whiteRabbit", "Whiterabbit" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { "whiteRabbit", "whiteRabbit", "whiteRabbit", "WhiteRabbit" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "whiteRabbit"; verify_case(4, Arg2, getWinner(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  RabbitVoting ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
