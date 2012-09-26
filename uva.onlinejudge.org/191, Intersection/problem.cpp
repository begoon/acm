#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <limits>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#ifdef _DEBUG
#include <windows.h>
#endif
using namespace std;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

const double EPS = 1e-9;

#define int_ long long

struct point {
  point() : x(0), y(0) {}
  point(int ax, int ay) : x(ax), y(ay) {}
  int x, y;
};
 
int square(point a, point b, point c) {
  return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}
 
bool intersect_1(int a, int b, int c, int d) {
  return max(a, b) >= min(c, d) && max(c, d) >= min(a, b);
}

bool intersect(point a, point b, point c, point d) {
  int s11 = square(a, b, c);
  int s12 = square(a, b, d);
  int s21 = square(c, d, a);
  int s22 = square(c, d, b);
  if (s11 == 0 && s12 == 0 && s21 == 0 && s22 == 0)
    return intersect_1(a.x, b.x, c.x, d.x) && intersect_1(a.y, b.y, c.y, d.y);
  else
    return s11 * s12 <= 0 && s21 * s22 <= 0;
}

int triangle_square_2(int x1, int y1, int x2, int y2, int x3, int y3) {
  return x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
}
 
double triangle_square(int x1, int y1, int x2, int y2, int x3, int y3) {
  return abs(triangle_square_2(x1, y1, x2, y2, x3, y3)) / 2.0;
}
 
bool counter_clockwise(int x1, int y1, int x2, int y2, int x3, int y3) {
  return triangle_square_2(x1, y1, x2, y2, x3, y3) > 0;
}

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  for (int i = 0; i < n; ++i) {
    point a, b, c, d;
    is >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    if (c.x > d.x) swap(c.x, d.x);
    if (c.y > d.y) swap(c.y, d.y);
    // Check if any edge intersects the segment.
    bool s1 = intersect(a, b, c, point(c.x, d.y));
    bool s2 = intersect(a, b, point(c.x, d.y), d);
    bool s3 = intersect(a, b, d, point(d.x, c.y));
    bool s4 = intersect(a, b, point(d.x, c.y), c);
    bool s = s1 || s2 || s3 || s4;
    // Check that it least one point is inside the rectange.
    bool a1 = counter_clockwise(c.x, c.y, d.x, c.y, a.x, a.y);
    bool a2 = counter_clockwise(d.x, c.y, d.x, d.y, a.x, a.y);
    bool a3 = counter_clockwise(d.x, d.y, c.x, d.y, a.x, a.y);
    bool a4 = counter_clockwise(c.x, d.y, c.x, c.y, a.x, a.y);
    bool aa = a1 && a2 && a3 && a4;
    os << (s || aa ? "T" : "F") << endl;
  }
}

const char* liner = "--------";
int problem;
int problem_filter;

#ifdef int
#undef int
#endif

void run(int line, const char* input, const char* output) {
  problem += 1;
  if (problem_filter != -1 && problem_filter != problem) return;

  stringstream is(input);
  stringstream os;
  solve(is, os);
  if (os.str() != output) {
    cerr << "Case #" << problem << ": FAILED (line " << line << ")" << endl;
#ifdef _DEBUG
    stringstream error;
    error << __FILE__ << "(" << line << "): error: test case " << problem << " FAILED" << endl;
    OutputDebugStringA(error.str().c_str());  
#endif
    cerr << liner << "EXPECTED" << liner << endl << output;
    cerr << liner << "-ACTUAL-" << liner << endl << os.str() 
         << liner << liner << liner << endl;
  } else 
    cerr << "Case #" << problem << " OK (line " << line << ")" << endl;
}

int main(int argc, char* argv[]) {
#ifdef TESTING_

problem = -1;
problem_filter = -1;

run(__LINE__,
"1\n"
"1 1 2 2 0 0 10 10\n"
,
"T\n"
);

run(__LINE__,
"1\n"
"1 1 2 2 0 10 10 0\n"
,
"T\n"
);

run(__LINE__,
"1\n"
"1 1 2 2 10 0 0 10\n"
,
"T\n"
);

run(__LINE__,
"1\n"
"2 4 4 2 1 1 11 11\n"
,
"T\n"
);

run(__LINE__,
"2\n"
"4 9 11 2 1 5 7 1\n"
"2 4 4 2 1 1 3 3\n"
,
"F\n"
"T\n"
);

run(__LINE__,
"68\n"
"4 9 11 2 1 1 7 5\n"
"11 2 4 9 1 1 7 5\n"
"12 12 24 24 19 5 25 17\n"
"4 6 15 9 1 1 11 11\n"
"19 5 25 17 12 12 24 24\n"
"0 18 8 12 1 1 11 11\n"
"2 4 4 2 1 1 11 11\n"
"-4 9 -11 2 -1 1 -7 5\n"
"-11 2 -4 9 -1 1 -7 5\n"
"-12 12 -24 24 -19 5 -25 17\n"
"-4 6 -15 9 -1 1 -11 11\n"
"-19 5 -25 17 -12 12 -24 24\n"
"0 18 -8 12 -1 1 -11 11\n"
"-2 4 -4 2 -1 1 -11 11\n"
"4 -9 11 -2 1 -1 7 -5\n"
"11 -2 4 -9 1 -1 7 -5\n"
"12 -12 24 -24 19 -5 25 -17\n"
"4 -6 15 -9 1 -1 11 -11\n"
"19 -5 25 -17 12 -12 24 -24\n"
"0 -18 8 -12 1 -1 11 -11\n"
"2 -4 4 -2 1 -1 11 -11\n"
"-4 -9 -11 -2 -1 -1 -7 -5\n"
"-11 -2 -4 -9 -1 -1 -7 -5\n"
"-12 -12 -24 -24 -19 -5 -25 -17\n"
"-4 -6 -15 -9 -1 -1 -11 -11\n"
"-19 -5 -25 -17 -12 -12 -24 -24\n"
"0 -18 -8 -12 -1 -1 -11 -11\n"
"-2 -4 -4 -2 -1 -1 -11 -11\n"
"9 1 9 2 4 3 9 6\n"
"9 2 9 1 4 3 9 6\n"
"10 3 13 3 4 3 9 6\n"
"13 3 10 3 4 3 9 6\n"
"10 6 14 6 4 3 9 6\n"
"14 6 10 6 4 3 9 6\n"
"9 7 9 10 4 3 9 6\n"
"9 10 9 7 4 3 9 6\n"
"4 7 4 10 4 3 9 6\n"
"4 10 4 7 4 3 9 6\n"
"0 6 3 6 4 3 9 6\n"
"3 6 0 6 4 3 9 6\n"
"1 3 3 3 4 3 9 6\n"
"3 3 1 3 4 3 9 6\n"
"4 0 4 2 4 3 9 6\n"
"4 2 4 0 4 3 9 6\n"
"5 3 8 5 4 3 9 6\n"
"8 5 5 3 4 3 9 6\n"
"5 3 8 3 4 3 9 6\n"
"8 3 5 3 4 3 9 6\n"
"6 4 6 5 4 3 9 6\n"
"6 5 6 4 4 3 9 6\n"
"4 3 9 6 4 3 9 6\n"
"9 6 4 3 4 3 9 6\n"
"4 3 5 4 4 3 9 6\n"
"5 4 4 3 4 3 9 6\n"
"5 3 8 3 4 3 9 6\n"
"8 3 5 3 4 3 9 6\n"
"5 3 9 3 4 3 9 6\n"
"9 3 5 3 4 3 9 6\n"
"4 4 4 5 4 3 9 6\n"
"4 5 4 4 4 3 9 6\n"
"4 3 4 5 4 3 9 6\n"
"4 5 4 3 4 3 9 6\n"
"4 3 4 6 4 3 9 6\n"
"4 6 4 3 4 3 9 6\n"
"9 2 9 5 4 3 9 6\n"
"9 5 9 2 4 3 9 6\n"
"9 2 9 7 4 3 9 6\n"
"9 7 9 2 4 3 9 6\n"
,
"F\n" 
"F\n" 
"F\n" 
"T\n" 
"T\n" 
"F\n" 
"T\n" 
"F\n" 
"F\n" 
"F\n" 
"T\n" 
"T\n" 
"F\n" 
"T\n" 
"F\n" 
"F\n" 
"F\n" 
"T\n" 
"T\n" 
"F\n" 
"T\n" 
"F\n" 
"F\n" 
"F\n" 
"T\n" 
"T\n" 
"F\n" 
"T\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"F\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n" 
"T\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

// ifstream is("INPUT.TXT");
// ofstream os("OUTPUT.TXT");
istream& is = cin;
ostream& os = cout;

solve(is, os);

#endif

return 0;
}

