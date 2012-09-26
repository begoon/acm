// BEGIN CUT HERE
// PROBLEM STATEMENT
// Instant run-off voting is a system for selecting the most preferred candidate in an election.  At the beginning of the 
// process, each voter ranks the candidates from most preferred to least preferred.  A series of automated voting rounds 
// are then held to determine the overall winner.
// 
// In each round, each voter casts a single vote for his most preferred remaining candidate.  If a candidate receives 
// strictly more than 50% of the votes cast in that round, that candidate is declared the winner of the election.  
// Otherwise, the candidate with the fewest votes in that round is eliminated, and another round is held.  If multiple 
// candidates are tied for the least number of votes, they are all eliminated.  If all the candidates are eliminated, the 
// election ends without a winner.
// 
// You are given the preferences of the voters in an election, and you must determine the outcome.  There are N 
// candidates numbered 0 to N-1, inclusive.  The preferences are given in a vector <string> voters, where each element 
// describes the preferences of a single voter.  This is a permutation of the digits 0 to N-1 in decreasing order of 
// preference.  In other words, the first digit is the voter's most preferred candidate, the second digit is his second 
// most preferred candidate, and so on.  Return the number of the candidate who wins the election, or -1 if the election 
// ends without a winner.
// 
// DEFINITION
// Class:InstantRunoffVoting
// Method:winner
// Parameters:vector <string>
// Returns:int
// Method signature:int winner(vector <string> voters)
// 
// 
// CONSTRAINTS
// -voters will contain between 1 and 50 elements, inclusive.
// -Each element of voters will contain between 1 and 10 characters, inclusive.
// -Each element of voters will contain the same number of characters.
// -Each element of voters will be a permutation of the digits between 0 and N-1, where N is the number of characters in 
// each element of voters.
// 
// 
// EXAMPLES
// 
// 0)
// {"01","10","01","01","10"}
// 
// Returns: 0
// 
// In the first round, candidate 0 gets 3 votes and candidate 1 gets 2 votes, so candidate 0 wins.
// 
// 1)
// {"120","102","210","021","012"}
// 
// Returns: 1
// 
// Nobody gets an absolute majority in the first round and candidate 2 is eliminated. Candidate 1 then receives 3 votes 
// in the next round, giving an absolute majority.
// 
// 2)
// {"10","01"}
// 
// Returns: -1
// 
// Each candidate gets 1 vote, so nobody can be declared winner.
// 
// 3)
// {"3120","3012","1032"
// ,"3120","2031","2103"
// ,"1230","1230"}
// 
// Returns: -1
// 
// Candidate 0 is eliminated in the first round of voting.  Candidate 2 is eliminated in the second round.   In the third 
// round, candidates 1 and 3 get 4 votes each.  Neither candidate receives an absolute majority, and they are both 
// eliminated for having the least number of votes, so the election ends without a winner.
// 
// 4)
// {"24103","30412","32014","21043","30412"
// ,"32401","14203","04123","30241","02413"
// ,"13042","01432","01342","32401","24301"
// ,"12430","41023","02413","42310","12043"}
// 
// Returns: 1
// 
// 
// 
// 5)
// {"0649853172","2146875039","2671548309"
// ,"5897216403","4719823056","7945213860"
// ,"9021538647","9286145307","9176403528"
// ,"3709486152"}
// 
// Returns: 9
// 
// 
// 
// END CUT HERE

#line 94 "problem.cpp"
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
#include <limits>
#include <cmath>
using namespace std;

class InstantRunoffVoting { 
  public: 
    int winner(vector <string> voters)  { 
      int r = -1;
      int total_candidates = voters[0].length();
      int candidates = total_candidates;
      vector<bool> deleted(total_candidates, false);
      while (candidates > 0) {
        vector<int> round(total_candidates, 0);
        for (int i = 0; i < voters.size(); ++i)
          round[voters[i][0] - '0'] += 1;
        int best = -1;
        int best_index;
        int best_count = 0;
        int worse = numeric_limits<int>::max();
        for (int i = 0; i < round.size(); ++i) {
          if (deleted[i]) continue;
          if (round[i] >= best) {
            best = round[i];
            best_index = i;
            best_count += 1;
          }
          if (round[i] < worse)
            worse = round[i];
        }
        if (best_count == 1) {
          double b = (double)best / voters.size();
          if (b > 0.5)
            return best_index;
        }
        for (int i = 0; i < round.size(); ++i)
          if (round[i] == worse) {
            for (int j = 0; j < voters.size(); ++j) {
              int n = voters[j].find('0' + i);
              voters[j].erase(n, 1);
            }
            candidates -= 1;
            deleted[i] = true;
          }
      }

      return r;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"01","10","01","01","10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, winner(Arg0)); }
	void test_case_1() { string Arr0[] = {"120","102","210","021","012"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, winner(Arg0)); }
	void test_case_2() { string Arr0[] = {"10","01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, winner(Arg0)); }
	void test_case_3() { string Arr0[] = {"3120","3012","1032"
,"3120","2031","2103"
,"1230","1230"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, winner(Arg0)); }
	void test_case_4() { string Arr0[] = {"24103","30412","32014","21043","30412"
,"32401","14203","04123","30241","02413"
,"13042","01432","01342","32401","24301"
,"12430","41023","02413","42310","12043"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, winner(Arg0)); }
	void test_case_5() { string Arr0[] = {"0649853172","2146875039","2671548309"
,"5897216403","4719823056","7945213860"
,"9021538647","9286145307","9176403528"
,"3709486152"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(5, Arg1, winner(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  InstantRunoffVoting ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
