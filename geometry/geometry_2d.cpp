#include "bits/stdc++.h"

using namespace std;

struct point2 {
  long long x, y; // WARNING!! CHECK RANGE OF COORDINATES FIRST!
  point2() : x(0), y(0) {}
  point2(long long _x, long long _y) : x(_x), y(_y) {}

  bool operator < (const point2 &r) const {
    if (y != r.y) return y < r.y;
    return x < r.x;
  }

  bool operator == (const point2 &r) const { return x == r.x and y == r.y; }
};

int ccw(point2 &p1, point2 &p2, point2 &p3) {
  long long res = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
  if (res == 0) return 0;
  if (res < 0) return -1;
  return 1;
}

double dist(point2 &a, point2 &b) { return hypot(a.x - b.x, a.y - b.y); }

double polygon_area(vector<point2> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += pvec[i].x * pvec[i + 1].y - pvec[i + 1].x * pvec[i].y;
  }
  return fabs(ret) / 2;
}

double polygon_perimeter(vector<point2> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += dist(pvec[i], pvec[i + 1]);
  }
  return ret;
}

vector<point2> convexhull(vector<point2> &pvec) {
  point2 pivot;
  auto it = pvec.begin();
  int n = pvec.size();

  if (n == 1) return pvec;
  if (n == 2) {
    if (pvec[0] == pvec[1]) pvec.pop_back();
    return pvec;
  }

  int piv_idx = 0;

  for (int i = 1; i < n; ++i)
    if (pvec[piv_idx].y > pvec[i].y or (pvec[piv_idx].y == pvec[i].y and pvec[piv_idx].x > pvec[i].x))
      piv_idx = i;

  point2 temp = pvec[0];
  pivot = pvec[0] = pvec[piv_idx];
  pvec[piv_idx] = temp;

  sort(it + 1, pvec.end(), [&](point2 &l, point2 &r) {
    int dir = ccw(pivot, l, r);
    if (!dir) return dist(pivot, l) < dist(pivot, r);
    return dir == 1;
  });

  vector<point2> ret(it, it + 2);

  int idx = 2, last;

  while (idx < n) {
    last = (int)ret.size() - 1;

    while (ret.size() >= 2 && ccw(ret[last - 1], ret[last], pvec[idx]) <= 0) {
      --last;
      ret.pop_back();
    }

    ret.push_back(pvec[idx++]);
  }

  return ret;
}


point2 rot_transform(point2 &p, double theta) {
  double rad = theta * acos(-1);
  return point2(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}
