#include "bits/stdc++.h"

using namespace std;

template<typename T>
struct point2 {
  T x, y;
  point2() : x(0), y(0) {}
  point2(T _x, T _y) : x(_x), y(_y) {}

  bool operator < (const point2<T> &r) const {
    if (abs(x - r.x) >= 1e-9) return x < r.x;
    return y < r.y;
  }

  bool operator == (const point2<T> &r) const {
    return (abs(r.x - x) < 1e-9 and abs(r.y - y) < 1e-9);
  }
};

template<typename T>
int ccw(point2<T> p1, point2<T> p2, point2<T> p3) {
  T res = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  if (abs(res) < 1e-12) return 0;
  if (res < 0) return -1;
  return 1;
}

template<typename T>
double ec_dist(point2<T> &a, point2<T> &b) { return hypot(a.x - b.x, a.y - b.y); }

template<typename T>
T det2(T a, T b, T c, T d) { return a*d - b*c; }

template<typename T>
double polygon_area(vector<point2<T>> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += pvec[i].x * pvec[i + 1].y - pvec[i + 1].x * pvec[i].y;
  }
  return abs(ret) / 2;
}

template<typename T>
double polygon_perimeter(vector<point2<T>> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += dist(pvec[i], pvec[i + 1]);
  }
  return ret;
}

template<typename T>
point2<double> rot_transform(point2<T> &p, double theta) {
  double rad = theta * acos(-1) / 180.;
  return point2<double>(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

template<typename T>
vector<point2<T>> convexhull(vector<point2<T>> &pvec) {
  int n = pvec.size();

  if (n <= 2) {
    if (n == 2 and pvec[0] == pvec[1]) pvec.pop_back();
    return pvec;
  }

  swap(pvec[0], *min_element(pvec.begin(), pvec.end()));
  auto it = pvec.begin();

  sort(it + 1, pvec.end(), [&](point2<T> &l, point2<T> &r) {
    int dir = ccw(*it, l, r);
    if (!dir) return dist(*it, l) < dist(*it, r);
    return dir == 1;
  });

  vector<point2<T>> ret(it, it + 2);

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

template<typename T>
struct line2 { T a, b, c; };

bool line_equation(point2<long long> &p, point2<long long> &q, line2<long long> &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  auto de = gcd(gcd(abs(a), abs(b)), abs(c));
  a /= de, b /= de, c /= de;
  if (a < 0 or (a == 0 and b < 0)) a *= -1, b *= -1, c *= -1;
  res = {a, b, c};
  return true;
}

bool line_equation(point2<double> &p, point2<double> &q, line2<double> &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  auto de = sqrt(a * a + b * b);
  a /= de, b /= de, c /= de;
  if (a <= -1e-9 or (abs(a) < 1e-9 and b <= -1e-9)) a = -a, b = -b, c = -c;
  return true;
}

template<typename T>
bool line_intersect(line2<T> &m, line2<T> &n, point2<double> &res) {
  auto zn = det2(m.a, m.b, n.a, n.b);
  if (typeid(T) == typeid(long long)) {
    if (zn == 0) return false;
  } else {
    if (abs(zn) < 1e-9) return false;
  }
  res.x = -det2(m.c, m.b, n.c, n.b) / zn;
  res.y = -det2(m.a, m.c, n.a, n.c) / zn;
  return true;
}

bool line_parallel(line2<long long> &m, line2<long long> &n) {
  return m.a == n.a and m.b == n.b;
}

bool line_parallel(line2<double> &m, line2<double> &n) {
  return abs(det2(m.a, m.b, n.a, n.b)) < 1e-9;
}

bool line_equiv(line2<long long> &m, line2<long long> &n) {
  return !det2(m.a, m.b, n.a, n.b) and !det2(m.a, m.c, n.a, n.c) and !det2(m.b, m.c, n.b, n.c);
}

bool line_equiv(line2<double> &m, line2<double> &n) {
  return abs(det2(m.a, m.b, n.a, n.b)) < 1e-9 and
         abs(det2(m.a, m.c, n.a, n.c)) < 1e-9 and
         abs(det2(m.b, m.c, n.b, n.c)) < 1e-9;
}

template<typename T>
struct mvec2 {
  T x, y;
  mvec2(T _x, T _y) : x(_x), y(_y) {}
  mvec2() { mvec2(0, 0); }
};

template<typename T>
mvec2<T> get_mvec2(point2<T> p, point2<T> q) { return {q.x - p.x, q.y - p.y}; }

template<typename T>
mvec2<T> mvec2_scalar(mvec2<T> _v, long long val) { return {_v.x * val, _v.y * val}; }

template<typename T>
mvec2<double> mvec2_scalar(mvec2<T> _v, double val) { return {_v.x * val, _v.y * val}; }

template<typename T>
inline T dot_prod(mvec2<T> &v1, mvec2<T> &v2) { return v1.x * v2.x + v1.y * v2.y; }

template<typename T>
inline T norm_sq(mvec2<T> &_v) { return _v.x * _v.x + _v.y * _v.y; }

template<typename T>
point2<T> point2_translate(point2<T> p, mvec2<long long> &_v) {
  return {p.x + _v.x, p.y + _v.y};
}

template<typename T>
point2<double> point2_translate(point2<T> p, mvec2<double> _v) {
  return {p.x + _v.x, p.y + _v.y};
}

template<typename T>
double dist2line(point2<T> p, point2<T> a, point2<T> b, point2<double> &c) {
  mvec2<T> ap = get_mvec2(a, p), ab = get_mvec2(a, b);
  auto u = (double)dot_prod(ap, ab) / norm_sq(ab);
  c = point2_translate<T>(a, mvec2_scalar(ab, u));
  return hypot(p.x - c.x, p.y - c.y);
}

template<typename T>
double dist2segment(point2<T> p, point2<T> a, point2<T> b, point2<double> &c) {
  mvec2<T> ap = get_mvec2(a, p), ab = get_mvec2(a, b);
  auto u = (double)dot_prod(ap, ab) / norm_sq(ab);
  if (u < 0) {
    c.x = a.x, c.y = a.y;
    return hypot(p.x - a.x, p.y - a.y);
  }
  if (u > 1) {
    c.x = b.x, c.y = b.y;
    return hypot(p.x - b.x, p.y - b.y);
  }
  return dist2line(p, a, b, c);
}

template<typename T>
double angle(point2<T> a, point2<T> o, point2<T> b) {
  auto oa = get_mvec2<T>(o, a), ob = get_mvec2<T>(o, b);
  return acos(dot_prod(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

template<typename T>
bool get_circle_center(point2<T> p1, point2<T> p2, double r, point2<double> &c) {
  // When need opposing center, swap points
  double d2 = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  double det = r * r / d2 - 0.25;
  if (det < 0.) return false;
  double h = sqrt(det);
  c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
  c.y = (p1.y + p2.y) * 0.5 + (p1.x - p2.x) * h;
  return true;
}

template<typename T>
bool is_convex(const vector<point2<T>> &pv) {
  int sz = pv.size();
  if (sz <= 3) return false;
  bool is_left = ccw(pv[0], pv[1], pv[2]) == 1;
  for (int i = 0; i < sz - 1; i++) {
    if ((ccw(pv[i], pv[i + 1], pv[(i + 2) == sz ? 1 : i + 2]) == 1) != is_left) return false;
  }
  return true;
}

template<class T>
bool in_polygon(point2<T> p, const vector<point2<T>> &pv) {
  int cnt = 0;
  for (int i = 0; i < pv.size(); i++) {
    int j = (i + 1) % pv.size();
    if (p.y < pv[i].y != p.y < pv[j].y) {
      auto x = (long double)(pv[j].x - pv[i].x) * (p.y - pv[i].y) / (pv[j].y - pv[i].y) + pv[i].x;
      if (p.x < x) ++cnt;
    }
  }
  return cnt & 1;
}
