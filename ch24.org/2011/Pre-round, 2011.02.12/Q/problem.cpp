#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include <deque>
#include <cmath>
#include <cassert>
#include <stdint.h>

using namespace std;

int h, w, maxg;
int data[2000][2000];
std::vector<std::vector<int> > vis;

std::pair<int, int> fbest(int x, int y) {
  const int maxdep = 5;
  std::pair<int, int> ret;
  int bestPrice = -1;
  for (int i = -maxdep; i <= maxdep; ++i)
    for (int j = -maxdep; j <= maxdep; ++j) {
      int xx = x + i, yy = y + j;
      if (xx < 0 || xx >= w || yy < 0 || yy >= h) continue;
      if (vis[yy][xx]) continue;
      if (bestPrice < data[yy][xx]) {
        bestPrice = data[yy][xx];
        ret = std::make_pair(xx, yy);
      }
    }
  assert(bestPrice != 1);
  return ret;
}

double calcDist(std::pair<int, int> p1, std::pair<int, int> p2) {
  double dx = p1.first - p2.first;
  double dy = p1.second - p2.second;
  double ret = dx * dx + dy * dy;
  return sqrt(ret);
}

bool canMoveback(std::pair<int, int> p, const std::vector<std::pair<int, int> >& vs, double dst) {
  double back = calcDist(*vs.begin(), p);
  double forward = calcDist(vs.back(), p);
  double all = dst + forward + back;
  return all < 4000;
}

std::vector<std::pair<int, int> > solve(int x = 0, int y = 0) {
  const int maxdx = 50;
  vis.assign(h, std::vector<int>(w, 0));
  double dst = 0;
  std::vector<std::pair<int, int> > vs;
  int nfail = 0;
  vs.push_back(std::make_pair(x, y));
  while (vs.size() < 500) {
    int xx = vs.back().first + (rand() % maxdx - maxdx / 2);
    int yy = vs.back().second + (rand() % maxdx - maxdx / 2);
    if (xx < 0 || xx >= w) continue;
    if (yy < 0 || yy >= h) continue;
    std::pair<int, int> best = fbest(xx, yy);
    if (canMoveback(best, vs, dst)) { 
      dst += calcDist(vs.back(), best);
      vis[best.second][best.first] = 1;
      vs.push_back(best);
      //std::cerr << "Move found!" << std::endl;
    } else {
      ++nfail;
      if (nfail > 10000) break;
      continue;
    }
  }
  return vs;
}

int eval(std::vector<std::pair<int, int> > vs) {
  int ret = 0;
  for (int i = 0; i < vs.size(); ++i)
    ret += data[vs[i].second][vs[i].first];
  return ret;
}

int main() {
srand(time(NULL));
  char filename[100];
  gets(filename);
  scanf("%d %d\n", &h, &w);
  scanf("%d\n", &maxg);
  std::cerr << "MAX g: " << maxg << std::endl;
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j) {
      unsigned char t; scanf("%c", &t);
      data[i][j] = t;
    }
  std::vector<std::pair<int, int> > vs = solve();
  int best = eval(vs);
  for (int i = 0; i < 100; ++i) {
    {
      std::vector<std::pair<int, int> > v = solve(rand() % w, h - 1);
      int c = eval(v);
      if (c > best) {
        best = c;
        vs = v;
      }
    }
  }
  for (int i = 0; i < vs.size(); ++i) {
    printf("%d %d\n", vs[i].first, vs[i].second);
  }
  return 0;
}