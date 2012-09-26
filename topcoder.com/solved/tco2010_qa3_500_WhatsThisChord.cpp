// BEGIN CUT HERE
// PROBLEM STATEMENT
// 
// In this problem your goal is to convert a description of how a guitar chord is played to its name. For the purpose of 
// this problem we will only consider major and minor chords.
// 
// 
// 
// Musical notes are given the following 12 names, in ascending order: 
// 
// C, C#, D, D#, E, F, F#, G, G#, A, A#, B.
// 
// 
// 
// The difference between two succesive notes is called a half-step.
// The order of notes is cyclic. That is, the note one half-step higher than B is again C, and the note two half-steps 
// lower than C is A#.
// Notes that are a multiple of 12 half-steps apart have the same name, and for our purposes we will consider them 
// equivalent.
// 
// 
// 
// In this problem we will consider a six-string guitar with standard tuning. 
// The six strings of such a guitar are tuned to the following notes, in order: E, A, D, G, B, E.
// (Guitar players, please note that the order used starts with the lowest string.)
// 
// 
// 
// If you play an open string, you will hear the corresponding note. For example, if you play the A string, you will hear 
// the note A.
// 
// To change the note the string plays, you can hold it down on one of the frets. If you play a string while holding it 
// down on the K-th fret, you will hear a note that is K half-steps higher.
// For example, if you play the A string while holding it down on the 4-th fret, you will hear the note C#.
// 
// 
// 
// You will be given a guitar chord encoded as a vector <int> chord with six elements, each of them describing one string 
// of the guitar in the order given above. For each string we are given the fret where to hold it down. The value 0 
// represents an open string that plays the original note, and the special value -1 is used for a string that is not 
// played in the chord.
// 
// 
// 
// For example, suppose that chord = {-1, 3, 2, 0, 1, 0}.
// 
// When playing this chord, you will hear the following notes: {none, C, E, G, C, E}.
// 
// 
// 
// The above chord contains three distinct notes: C, E, and G. This chord is called the "C Major" chord.
// 
// 
// 
// For any note X, the "X Major" chord is formed by three distinct notes. It can be obtained from the "C Major" chord by 
// shifting all three notes by the same number of steps so that C becomes X.
// For example, if we shift the notes (C,E,G) by three steps, we get the notes (D#,G,A#). These three notes form the "D# 
// Major" chord.
// 
// 
// 
// Similarly, the chord "C Minor" is formed by the notes C, D#, and G, and all other minor chords are shifts of this chord.
// 
// 
// 
// Given the vector <int> chord, decide whether it is one of the 12 major or one of the 12 minor chords, as defined 
// above. If it is one of these chords, return its name as a string ("X Major" for major chords, "X Minor" for minor 
// chords). If the chord represented by chord is not one of our chords, return an empty string.
// 
// 
// DEFINITION
// Class:WhatsThisChord
// Method:classify
// Parameters:vector <int>
// Returns:string
// Method signature:string classify(vector <int> chord)
// 
// 
// NOTES
// -When classifying a chord the only thing that matters is the set of notes played. The number of times a note is played 
// does not matter as long as each of the required notes is played at least once.
// 
// 
// CONSTRAINTS
// -chord will contain exactly 6 elements.
// -Each element of chord will be between -1 and 12, inclusive.
// 
// 
// EXAMPLES
// 
// 0)
// {-1, 3, 2, 0, 1, 0}
// 
// Returns: "C Major"
// 
// This is the C Major chord, as described in the problem statement.
// 
// 1)
// {3,2,0,0,0,3}
// 
// Returns: "G Major"
// 
// This is another of the basic guitar chords. The strings play the following notes: G, B, D, G, B, G. If we take the C 
// Major chord (C,E,G) and shift it by 7, we get (G,B,D), which is precisely the set of notes in this chord. Hence the 
// chord is G Major.
// 
// 2)
// {-1,0,2,2,1,0}
// 
// Returns: "A Minor"
// 
// This is the most common way of playing the A Minor chord. The three distinct notes we hear in this case are A, C, and E.
// 
// 3)
// {-1,4,3,1,2,1}
// 
// Returns: "C# Major"
// 
// 
// 
// 4)
// {8,10,10,9,8,8}
// 
// Returns: "C Major"
// 
// There are multiple ways to play each chord.
// 
// 5)
// {0,0,0,0,0,0}
// 
// Returns: ""
// 
// This is not one of our 24 simple chords.
// 
// 6)
// {-1,-1,4,-1,-1,7}
// 
// Returns: ""
// 
// Neither is this.
// 
// 7)
// {-1, -1, 2, 0, 1, 0}
// 
// Returns: "C Major"
// 
// The notes played in this chord are {none, none, E, G, C, E}. 
// The set of notes played is (C,E,G), hence this is again a C Major chord.
// (In music theory this chord has a more precise name C/E, but this is irrelevant. It is still a C Major chord.)
// 
// END CUT HERE

#line 154 "problem.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cmath>
using namespace std;

char* abr[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

class WhatsThisChord { 
  public: 
    string classify(vector <int> chord)  { 
      int ofs[6] = { 4, 9, 2, 7, 11, 4 };
      set<int> u;
      for (int i = 0; i < 6; ++i) if (chord[i] != -1) {
        u.insert((ofs[i] + chord[i]) % 12);
      }
      if (u.size() != 3) return "";
      for (int i = 0; i < 12; ++i) {
        if (u.count(i) && u.count((i+4) % 12) && u.count((i+7) % 12))
          return string(abr[i]) + " Major";
        if (u.count(i) && u.count((i+3) % 12) && u.count((i+7) % 12))
          return string(abr[i]) + " Minor";
      }
      return "";
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1, 3, 2, 0, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C Major"; verify_case(0, Arg1, classify(Arg0)); }
	void test_case_1() { int Arr0[] = {3,2,0,0,0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "G Major"; verify_case(1, Arg1, classify(Arg0)); }
	void test_case_2() { int Arr0[] = {-1,0,2,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "A Minor"; verify_case(2, Arg1, classify(Arg0)); }
	void test_case_3() { int Arr0[] = {-1,4,3,1,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C# Major"; verify_case(3, Arg1, classify(Arg0)); }
	void test_case_4() { int Arr0[] = {8,10,10,9,8,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C Major"; verify_case(4, Arg1, classify(Arg0)); }
	void test_case_5() { int Arr0[] = {0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(5, Arg1, classify(Arg0)); }
	void test_case_6() { int Arr0[] = {-1,-1,4,-1,-1,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = ""; verify_case(6, Arg1, classify(Arg0)); }
	void test_case_7() { int Arr0[] = {-1, -1, 2, 0, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "C Major"; verify_case(7, Arg1, classify(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
  WhatsThisChord ___test; 
  ___test.run_test(-1);
  getchar();
} 
// END CUT HER
