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

template <typename T>
T max(T a, T b, T c) {
  return max(a, max(b, c));
}

// --- BEGIN: bignum

#if 0
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;
#endif

const int MAXD = 1000, DIG = 1, BASE = 10;

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

void solve(istream& is, ostream& os) {
  int n;
  is >> n;
  bignum a0 = 1, a1 = 1;
  while (--n) {
    bignum t0 = a0 + a1;
    bignum t1 = a0;
    a0 = t0;
    a1 = t1;
  }
  os << (a0 + a1).str() << endl;
}

#undef int

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
"2\n"
,
"3\n"
);

run(__LINE__,
"3\n"
,
"5\n"
);

run(__LINE__,
"1000\n"
,
"113796925398360272257523782552224175572745930353730513145086634176691092536145985470146129334641866902783673042322088625863396052888690096969577173696370562180400527049497109023054114771394568040040412172632376\n"
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

