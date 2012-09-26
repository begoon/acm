#include <string>
#include <stack>
#include <iostream>
#include <cstdlib>
using namespace std;

int N;
string r;
stack<char> p;

void search() {
  if (r.length() == N) {
    cout << r << endl;
    return;
  }
  if (r.length() < N - p.size()) {
    for (const char* i = "(["; *i; ++i) {
      r += *i;
      p.push(*i);
      search();
      p.pop();
      r.resize(r.length() - 1);
    }
  }
  if (!p.empty()) {
    char o = p.top();
    char c = o == '(' ? ')' : ']';
    r += c;
    p.pop();
    search();
    p.push(o);
    r.resize(r.length() - 1);
  }
}

int main(int argc, char* argv[]) {
  freopen("INPUT.TXT", "r", stdin);
  freopen("OUTPUT.TXT", "w", stdout);
  cin >> N;
  search();
  return 0;
}

