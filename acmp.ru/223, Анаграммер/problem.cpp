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

int steps;

vector< vector< map< string, int > > > dp_bruteforce;

int anagram_bruteforce(istream& is, ostream& os, const string& from, int from_i, const string to, int to_i, string& q, int stack_i) {
  steps += 1;
  if (to_i >= to.length()) {
    if (from_i >= from.length() && stack_i == 0)
      return 1;
    return 0;
  }
  if (from_i < from.length()) {
    int cache = dp_bruteforce[from_i][to_i][q.substr(0, stack_i)];
    if (cache > 0)
      return cache;
  }
  int r = 0;
  if (from_i < from.length()) {
    assert(stack_i < q.length());
    q[stack_i] = from[from_i];
    r += anagram_bruteforce(is, os, from, from_i + 1, to, to_i, q, stack_i + 1);
  }
  if (stack_i > 0 && q[stack_i - 1] == to[to_i]) {
    char c = q[stack_i - 1];
    r += anagram_bruteforce(is, os, from, from_i, to, to_i + 1, q, stack_i - 1);
    q[stack_i - 1] = c;
  }

  if (from_i < from.length())
    dp_bruteforce[from_i][to_i][q.substr(0, stack_i)] = r;
  return r;
}

void solve_bruteforce(istream& is, ostream& os) {
  string from, to;
  getline(is, from);
  getline(is, to);
  steps = 0;
  string q(from.length() * 2, '.');
  dp_bruteforce = vector< vector< map< string, int > > >(
    from.length(), 
    vector< map< string, int > >(
      to.length(), map< string, int >()
    )
  );

  os << anagram_bruteforce(is, os, from, 0, to, 0, q, 0) << endl;
  cout << steps << endl;
}

// --- BEGIN: bignum

#if 0
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;
#endif

const int MAXD = 40, DIG = 1, BASE = 10;

const unsigned long long BOUND = 
  numeric_limits<unsigned long long>::max() - (unsigned long long)BASE * BASE;

struct bignum {
  int D, digits[MAXD / DIG + 2];

  inline void trim() {
    while (D > 1 && digits[D - 1] == 0)
      D--;
  }

  inline void init(long long x) {
    memset (digits, 0, sizeof (digits));
    D = 0;

    do {
      digits[D++] = x % BASE;
      x /= BASE;
    } while (x > 0);
  }

  inline bignum(long long x) {
    init (x);
  }

  inline bignum(int x = 0) {
    init (x);
  }

  inline bignum (const char* s) {
    memset(digits, 0, sizeof(digits));
    int len = strlen(s), first = (len + DIG - 1) % DIG + 1;
    D = (len + DIG - 1) / DIG;

    for (int i = 0; i < first; i++)
      digits[D - 1] = digits[D - 1] * 10 + s[i] - '0';

    for (int i = first, d = D - 2; i < len; i += DIG, d--)
      for (int j = i; j < i + DIG; j++)
        digits[d] = digits[d] * 10 + s[j] - '0';

    trim();
  }

  inline char* str() {
    trim();
    char *buf = new char[DIG * D + 1];
    int pos = 0, d = digits[D - 1];

    do {
      buf[pos++] = d % 10 + '0';
      d /= 10;
    } while (d > 0);

    reverse(buf, buf + pos);

    for (int i = D - 2; i >= 0; i--, pos += DIG)
      for (int j = DIG - 1, t = digits[i]; j >= 0; j--) {
        buf[pos + j] = t % 10 + '0';
        t /= 10;
      }

    buf[pos] = '\0';
    return buf;
  }

  inline bool operator<(const bignum& o) const {
    if (D != o.D) return D < o.D;

    for (int i = D - 1; i >= 0; i--)
      if (digits[i] != o.digits[i])
        return digits[i] < o.digits[i];

      return false;
  }

  inline bool operator==(const bignum& o) const {
    if (D != o.D) return false;

    for (int i = 0; i < D; i++)
      if (digits[i] != o.digits[i])
        return false;

    return true;
  }

  inline bignum operator<<(int p) const {
    bignum temp;
    temp.D = D + p;

    for (int i = 0; i < D; i++)
      temp.digits[i + p] = digits[i];

    for (int i = 0; i < p; i++)
      temp.digits[i] = 0;

    return temp;
  }

  inline bignum operator>>(int p) const {
    bignum temp;
    temp.D = D - p;

    for (int i = 0; i < D - p; i++)
      temp.digits[i] = digits[i + p];

    for (int i = D - p; i < D; i++)
      temp.digits[i] = 0;

    return temp;
  }

  inline bignum range(int a, int b) const {
    bignum temp = 0;
    temp.D = b - a;

    for (int i = 0; i < temp.D; i++)
      temp.digits[i] = digits[i + a];

    return temp;
  }

  inline bignum operator+(const bignum& o) const {
    bignum sum = o;
    int carry = 0;

    for (sum.D = 0; sum.D < D || carry > 0; sum.D++) {
      sum.digits[sum.D] += (sum.D < D ? digits[sum.D] : 0) + carry;

      if (sum.digits[sum.D] >= BASE) {
        sum.digits[sum.D] -= BASE;
        carry = 1;
      } else
        carry = 0;
    }

    sum.D = max (sum.D, o.D);
    sum.trim();
    return sum;
  }

  inline bignum operator-(const bignum& o) const {
    bignum diff = *this;

    for (int i = 0, carry = 0; i < o.D || carry > 0; i++) {
      diff.digits[i] -= (i < o.D ? o.digits[i] : 0) + carry;

      if (diff.digits[i] < 0) {
        diff.digits[i] += BASE;
        carry = 1;
      } else
        carry = 0;
    }

    diff.trim();
    return diff;
  }

  inline bignum operator*(const bignum& o) const {
    bignum prod = 0;
    unsigned long long sum = 0, carry = 0;

    for (prod.D = 0; prod.D < D + o.D - 1 || carry > 0; prod.D++) {
      sum = carry % BASE;
      carry /= BASE;

      for (int j = max (prod.D - o.D + 1, 0); j <= min (D - 1, prod.D); j++) {
        sum += (unsigned long long) digits[j] * o.digits[prod.D - j];

        if (sum >= BOUND) {
          carry += sum / BASE;
          sum %= BASE;
        }
      }

      carry += sum / BASE;
      prod.digits[prod.D] = sum % BASE;
    }

    prod.trim();
    return prod;
  }

  inline double double_div(const bignum& o) const {
    double val = 0, oval = 0;
    int num = 0, onum = 0;

    for (int i = D - 1; i >= max (D - 3, 0); i--, num++)
      val = val * BASE + digits[i];

    for (int i = o.D - 1; i >= max (o.D - 3, 0); i--, onum++)
      oval = oval * BASE + o.digits[i];

      return val / oval * (D - num > o.D - onum ? BASE : 1);
  }

  inline pair<bignum, bignum> divmod(const bignum& o) const {
    bignum quot = 0, rem = *this, temp;

    for (int i = D - o.D; i >= 0; i--) {
      temp = rem.range (i, rem.D);
      int div = (int) temp.double_div(o);
      bignum mult = o * div;

      while (div > 0 && temp < mult) {
        mult = mult - o;
        div--;
      }

      while (div + 1 < BASE && !(temp < mult + o)) {
        mult = mult + o;
        div++;
      }

      rem = rem - (o * div << i);

      if (div > 0) {
        quot.digits[i] = div;
        quot.D = max (quot.D, i + 1);
      }
    }

    quot.trim();
    rem.trim();
    return make_pair(quot, rem);
  }

  inline bignum operator/(const bignum& o) const {
    return divmod(o).first;
  }

  inline bignum operator%(const bignum& o) const {
    return divmod(o).second;
  }

  inline bignum power(int exp) const {
    bignum p = 1, temp = *this;

    while (exp > 0) {
      if (exp & 1) p = p * temp;
      if (exp > 1) temp = temp * temp;
      exp >>= 1;
    }

    return p;
  }
};

inline bignum gcd(bignum a, bignum b) {
  bignum t;

  while (!(b == 0)) {
    t = a % b;
    a = b;
    b = t;
  }

  return a;
}

// --- END: bignum

map<int, bignum> dp;

bignum anagram(const string& from, int start_f, int end_f, const string& to, int start_t, int end_t) {
  assert(from.length() == to.length());
  int n = from.length();
  if (start_f >= end_f || start_t >= end_t) {
    steps += 1;
    return 1;
  }
  int memo_f = start_f * n + end_f - 1;
  int memo_t = start_t * n + end_t - 1;
  int memo = memo_f * n * n + memo_t;
  if (dp.find(memo) != dp.end())
    return dp[memo];
  assert(end_f - start_f == end_t - start_t);
  steps += 1;
  int x = 0;
  for (int i = 0; i < end_t - start_t; ++i)
    x ^= from[start_f + i] ^ to[start_t + i];
  if (x)
    return dp[memo] = 0;
  bignum t = 0;
  for (int i = 0; i < end_t - start_t; ++i) {
    if (from[start_f] != to[start_t + i]) continue;
    bignum l = anagram(from, start_f + 1, start_f + 1 + i, to, start_t, start_t + i);
    bignum r = anagram(from, start_f + i + 1, end_f, to, start_t + i + 1, end_t);
    t = t + l * r;
  }
  dp[memo] = t;
  return t;
}

void solve(istream& is, ostream& os) {
  string from, to;
  getline(is, from);
  getline(is, to);
  assert(from.length() == to.length());
  int n = from.length();
  steps = 0;
  dp = map<int, bignum>();
  os << anagram(from, 0, from.length(), to, 0, to.length()).str() << endl;
  cout << steps << endl;
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
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
,
"1978261657756160653623774456\n"
);

run(__LINE__,
"madammadammadammadammadammadammadammadammadammadam\n"
"adammadammadammadammadammadammadammadammadammadamm\n"
,
"9197706059701\n"
);

run(__LINE__,
"TROT\n"
"TORT\n"
,
"2\n"
);

run(__LINE__,
"MADAM\n"
"ADAMM\n"
,
"4\n"
);

run(__LINE__,
"LONG\n"
"GONG\n"
,
"0\n"
);

run(__LINE__,
"AAAAAAAA\n"
"AAAAAAAA\n"
,
"1430\n"
);

#ifdef _DEBUG
getchar();
#endif

#else

ifstream is("INPUT.TXT");
ofstream os("OUTPUT.TXT");
// istream& is = cin;
// ostream& os = cout;

solve(is, os);

#endif

return 0;
}

