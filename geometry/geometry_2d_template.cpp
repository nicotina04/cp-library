#include "bits/stdc++.h"

using namespace std;

template<typename T>
struct point2 {
  T x, y;
  point2() : x(0), y(0) {}
  point2(T _x, T _y) : x(_x), y(_y) {}

  bool operator < (const point2<T> &r) const {
    if (typeid(T) == typeid(long long)) {
      if (x != r.x) return x < r.x;
      return y < r.y;
    } else {
      if (fabs(x - r.x) >= 1e-9) return x < r.x;
      return y < r.y;
    }
  }

  bool operator == (const point2<T> &r) const {
    if (typeid(T) == typeid(long long)) {
      return x == r.x and y == r.y;
    } else {
      return (fabs(r.x - x) < 1e-9 and fabs(r.y - y) < 1e-9);
    }
  }
};

template<typename T>
int ccw(point2<T> &p1, point2<T> &p2, point2<T> &p3) {
  T res = p1.x * p2.y + p3.x * p1.y + p2.x * p3.y - p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
  if (!res) return 0;
  if (res < 0) return -1;
  return 1;
}

template<typename T>
double dist(point2<T> &a, point2<T> &b) { return hypot(a.x - b.x, a.y - b.y); }

template<typename T>
T det2(T a, T b, T c, T d) { return a*d - b*c; }

template<typename T>
double polygon_area(vector<point2<T>> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += pvec[i].x * pvec[i + 1].y - pvec[i + 1].x * pvec[i].y;
  }
  return fabs(ret) / 2;
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
point2<double> rot_transform(point2<T> &p, double theta) {
  double rad = theta * acos(-1);
  return point2<double>(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

template<typename T>
struct line2 { T a, b, c; };

template<typename T>
bool line_equation(point2<T> &p, point2<T> &q, line2<T> &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  if (a < 0 or (a == 0 and b < 0)) a *= -1, b *= -1, c *= -1;
  double de = 1;
  if (typeid(T) == typeid(long long)) {
    de = gcd(gcd(a, b), c);
  } else {
    de = sqrt(a * a + b * b);
  }
  res = {a / (T)de, b / (T)de, c / (T)de};
  return true;
}

template<typename T>
bool line_intersect(line2<T> &m, line2<T> &n, point2<double> &res) {
  auto zn = det2(m.a, m.b, n.a, n.b);
  if (typeid(T) == typeid(long long)) {
    if (zn == 0) return false;
  } else {
    if (fabs(zn) < 1e-9) return false;
  }
  res.x = -det2(m.c, m.b, n.c, n.b) / zn;
  res.y = -det2(m.a, m.c, n.a, n.c) / zn;
  return true;
}

bool line_parallel(line2<long long> &m, line2<long long> &n) {
  return m.a == n.a and m.b == n.b;
}

bool line_parallel(line2<double> &m, line2<double> &n) {
return fabs(det2(m.a, m.b, n.a, n.b)) < 1e-9;
}

bool line_equiv(line2<long long> &m, line2<long long> &n) {
  return !det2(m.a, m.b, n.a, n.b) and !det2(m.a, m.c, n.a, n.c) and !det2(m.b, m.c, n.b, n.c);
}

bool line_equiv(line2<double> &m, line2<double> &n) {
  return fabs(det2(m.a, m.b, n.a, n.b)) < 1e-9 and
         fabs(det2(m.a, m.c, n.a, n.c)) < 1e-9 and
         fabs(det2(m.b, m.c, n.b, n.c)) < 1e-9;
}

template<typename T>
struct mvec2 {
     T x, y;
     mvec2(T _x, T _y) : x(_x), y(_y) {}
};
