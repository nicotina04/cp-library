#include "bits/stdc++.h"

using namespace std;

struct point2f {
  double x, y;
  point2f() : x(0.), y(0.) {}
  point2f(double _x, double _y) : x(_x), y(_y) {}

  bool operator < (const point2f &r) const {
    if (fabs(x - r.x) >= 1e-9) return x < r.x;
    return y < r.y;
  }

  bool operator == (const point2f &r) const {
    return (fabs(r.x - x) < 1e-9 and fabs(r.y - y) < 1e-9);
  }
};

struct point2 {
  long long x, y;
  point2() : x(0), y(0) {}
  point2(long long _x, long long _y) : x(_x), y(_y) {}

  bool operator < (const point2 &r) const {
    if (x != r.x) return x < r.x;
    return y < r.y;
  }

  bool operator == (const point2 &r) const { return x == r.x and y == r.y; }
};

int ccw(point2 &p1, point2 &p2, point2 &p3) {
  long long res = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
  if (res == 0) return 0;
  if (res < 0) return -1;
  return 1;
}

int ccw(point2f &p1, point2f &p2, point2f &p3) {
  double res = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
  if (fabs(res) < 1e-9) return 0;
  if (res < 0) return -1;
  return 1;
}

double dist(point2 &a, point2 &b) { return hypot(a.x - b.x, a.y - b.y); }

double dist(point2f &a, point2f &b) { return hypot(a.x - b.x, a.y - b.y); }

double det2(double a, double b, double c, double d) {
  return a*d - b*c;
}

long long det2(long long a, long long b, long long c, long long d) {
  return a*d - b*c;
}

double polygon_area(vector<point2> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += pvec[i].x * pvec[i + 1].y - pvec[i + 1].x * pvec[i].y;
  }
  return fabs(ret) / 2;
}

double polygon_area(vector<point2f> &pvec) {
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
  int n = pvec.size();

  if (n <= 2) {
    if (n == 2 and pvec[0] == pvec[1]) pvec.pop_back();
    return pvec;
  }

  swap(pvec[0], *min_element(pvec.begin(), pvec.end()));
  auto it = pvec.begin();

  sort(it + 1, pvec.end(), [&](point2 &l, point2 &r) {
    int dir = ccw(*it, l, r);
    if (!dir) return dist(*it, l) < dist(*it, r);
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

point2f rot_transform(point2 &p, double theta) {
  double rad = theta * acos(-1);
  return point2f(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

point2f rot_transform(point2f &p, double theta) {
  double rad = theta * acos(-1);
  return point2f(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

struct line2 { long long a, b, c; };

struct line2f { double a, b, c; };

bool line_equation(point2 &p, point2 &q, line2 &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  if (a < 0 or (a == 0 and b < 0)) a *= -1, b *= -1, c *= -1;
  auto g = gcd(gcd(a, b), c);
  res = {a / g, b / g, c / g};
  return true;
}

bool line_equation(point2f &p, point2f &q, line2f &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  if (a < 0 or (a == 0 and b < 0)) a *= -1, b *= -1, c *= -1;
  auto z = sqrt(a * a + b * b);
  res = {a / z, b / z, c / z};
  return true;
}

bool line_intersect(line2f &m, line2f &n, point2f &res) {
  auto zn = det2(m.a, m.b, n.a, n.b);
  if (fabs(zn) < 1e-9) return false;
  res.x = -det2(m.c, m.b, n.c, n.b) / zn;
  res.y = -det2(m.a, m.c, n.a, n.c) / zn;
  return true;
}

bool line_intersect(line2 &m, line2 &n, point2f &res) {
  auto zn = det2(m.a, m.b, n.a, n.b);
  if (zn == 0) return false;
  res.x = -det2(m.c, m.b, n.c, n.b) / (double)zn;
  res.y = -det2(m.a, m.c, n.a, n.c) / (double)zn;
  return true;
}

bool line_parallel(line2 &m, line2 &n) {
  return m.a == n.a and m.b == n.b;
}

bool line_parallel(line2f &m, line2f &n) {
  return fabs(det2(m.a, m.b, n.a, n.b)) < 1e-9;
}

bool line_equiv(line2 &m, line2 &n) {
  return !det2(m.a, m.b, n.a, n.b) and !det2(m.a, m.c, n.a, n.c) and !det2(m.b, m.c, n.b, n.c);
}

bool line_equiv(line2f &m, line2f &n) {
  return fabs(det2(m.a, m.b, n.a, n.b)) < 1e-9 and
  fabs(det2(m.a, m.c, n.a, n.c)) < 1e-9 and
  fabs(det2(m.b, m.c, n.b, n.c)) < 1e-9;
}

struct gvec2 {
  long long x, y;
  gvec2(long long _x, long long _y) : x(_x), y(_y) {}
};

struct gvec2f {
  double x, y;
  gvec2f(double _x, double _y) : x(_x), y(_y) {}
};

gvec2 get_gvec2(point2 &p, point2 &q) {
  return {q.x - p.x, q.y - p.y};
}

gvec2f get_gvec2f(point2f &p, point2f &q) {
  return {q.x - p.x, q.y - p.y};
}

gvec2 gvec2_scalar(gvec2 &_v, long long val) {
  return {_v.x * val, _v.y * val};
}

gvec2f gvec2f_scalar(gvec2f &_v, double val) {
  return {_v.x * val, _v.y * val};
}

long long dot_prod(gvec2 &v1, gvec2 &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

double dot_prod(gvec2f &v1, gvec2f &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
