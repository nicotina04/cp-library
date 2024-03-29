#include "bits/stdc++.h"

using namespace std;
using ll = int_fast64_t;

using ftype = double;
constexpr ftype eps = 1e-9;
template<typename T> struct point2 {
  T x, y;
  point2() : x(0), y(0) {}
  point2(T _x, T _y) : x(_x), y(_y) {}
  bool operator < (const point2<T> &o) const { return x != o.x ? x < o.x : y < o.y; }
  bool operator == (const point2<T> &o) const { return (abs(o.x - x) < eps and abs(o.y - y) < eps); }
};

template<typename T> int ccw(point2<T> p1, point2<T> p2, point2<T> p3) {
  T res = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  if (abs(res) < eps) return 0;
  if (res < 0) return -1;
  return 1;
}

template<typename T> double ec_dist(point2<T> &a, point2<T> &b) { return hypot(a.x - b.x, a.y - b.y); }

template<typename T> T det2(T a, T b, T c, T d) { return a*d - b*c; }

template<typename T> double polygon_area(vector<point2<T>> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += pvec[i].x * pvec[i + 1].y - pvec[i + 1].x * pvec[i].y;
  }
  return abs(ret) / 2;
}

template<typename T> double polygon_perimeter(vector<point2<T>> &pvec) {
  double ret = 0;
  for (int i = 0; i < (int)pvec.size() - 1; i++) {
    ret += ec_dist(pvec[i], pvec[i + 1]);
  }
  return ret;
}

template<typename T> vector<point2<T>> convexhull(vector<point2<T>> &pvec) {
  int n = pvec.size();
  if (n == 2 and pvec[0] == pvec[1]) pvec.pop_back();
  if (n <= 2) return pvec;
  sort(pvec.begin(), pvec.end());
  vector<point2<T>> dh(n), uh(n);
  int sz = 0;
  for (int i = 0; i < n; i++) {
    while (sz > 1 and ccw(dh[sz - 2], dh[sz - 1], pvec[i]) <= 0) --sz;
    dh[sz++] = pvec[i];
  }
  dh.resize(sz - 1);
  sz = 0;
  for (int i = n - 1; i >= 0; i--) {
    while (sz > 1 and ccw(uh[sz - 2], uh[sz - 1], pvec[i]) <= 0) --sz;
    uh[sz++] = pvec[i];
  }
  uh.resize(sz - 1);
  for (auto &item : uh) dh.push_back(item);
  return dh;
}

template<typename T> ll rot_calipers(vector<point2<T>> &hull) {
  int lo = 0, hi = 0, sz = hull.size();
  for (int i = 0; i < sz; i++) {
    if (hull[i] < hull[lo]) lo = i;
    if (hull[hi] < hull[i]) hi = i;
  }
  ll ret = dist_sq(hull[lo], hull[hi]); // define dist square
  for (int i = 0; i < sz; i++) {
    int flag = ccw({0, 0}, hull[(lo + 1) % sz] - hull[lo], hull[hi] - hull[(hi + 1) % sz]);
    if (flag == 1) lo = (lo + 1) % sz;
    else hi = (hi + 1) % sz;
    ret = max(ret, dist_sq(hull[lo], hull[hi]));
  }
  return ret;
}

template<typename T> bool is_convex(const vector<point2<T>> &pv) {
  int sz = pv.size();
  if (sz <= 3) return false;
  bool is_left = ccw(pv[0], pv[1], pv[2]) == 1;
  for (int i = 0; i < sz - 1; i++) {
    if ((ccw(pv[i], pv[i + 1], pv[(i + 2) == sz ? 1 : i + 2]) == 1) != is_left) return false;
  }
  return true;
}

template<typename T> bool in_polygon(point2<T> p, const vector<point2<T>> &pv) {
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

template<typename T> bool in_triangle(point2<T> target, point2<T> a, point2<T> b, point2<T> c) {
  int ab = ccw(a, b, target);
  int bc = ccw(b, c, target);
  int ca = ccw(c, a, target);
  if (!ab or !bc or !ca) return false; // no allow bound
  return ab == bc and bc == ca;
}

template<typename T> point2<ftype> rot_transform(point2<T> &p, double theta) {
  double rad = theta * acos(-1) / 180.;
  return point2<ftype>(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

template<typename T> struct line2 { T a, b, c; };

bool line_equation(point2<ll> &p, point2<ll> &q, line2<ll> &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  auto de = gcd(gcd(abs(a), abs(b)), abs(c));
  a /= de, b /= de, c /= de;
  if (a < 0 or (a == 0 and b < 0)) a *= -1, b *= -1, c *= -1;
  res = {a, b, c};
  return true;
}

bool line_equation(point2<ftype> &p, point2<ftype> &q, line2<ftype> &res) {
  if (p == q) return false;
  auto a = p.y - q.y, b = q.x - p.x;
  auto c = -a * p.x - b * p.y;
  auto de = sqrt(a * a + b * b);
  a /= de, b /= de, c /= de;
  if (a <= -eps or (abs(a) < eps and b <= -eps)) a = -a, b = -b, c = -c;
  return true;
}

template<typename T> bool line_intersect(line2<T> &m, line2<T> &n, point2<ftype> &res) {
  auto zn = det2(m.a, m.b, n.a, n.b);
  if (typeid(T) == typeid(long long)) {
    if (zn == 0) return false;
  } else if (abs(zn) < eps) return false;
  res.x = -det2(m.c, m.b, n.c, n.b) / zn;
  res.y = -det2(m.a, m.c, n.a, n.c) / zn;
  return true;
}

bool line_parallel(line2<ll> &m, line2<ll> &n) { return m.a == n.a and m.b == n.b; }
bool line_parallel(line2<ftype> &m, line2<ftype> &n) { return abs(det2(m.a, m.b, n.a, n.b)) < 1e-9; }

bool line_equiv(line2<ll> &m, line2<ll> &n) { return !det2(m.a, m.b, n.a, n.b) and !det2(m.a, m.c, n.a, n.c) and !det2(m.b, m.c, n.b, n.c); }
bool line_equiv(line2<ftype> &m, line2<ftype> &n) {
  return abs(det2(m.a, m.b, n.a, n.b)) < eps and
         abs(det2(m.a, m.c, n.a, n.c)) < eps and
         abs(det2(m.b, m.c, n.b, n.c)) < eps;
}

template<typename T> struct vect2 {
  T x, y;
  vect2(T _x, T _y) : x(_x), y(_y) {}
  vect2() { vect2(0, 0); }
};

template<typename T> vect2<T> get_mvec2(point2<T> p, point2<T> q) { return {q.x - p.x, q.y - p.y}; }

template<typename T, typename U> vect2<T> mvec2_scalar(vect2<T> _v, U val) { return {_v.x * val, _v.y * val}; }

template<typename T, typename U> T cross(vect2<U> a, vect2<U> b) { return a.x * b.y - a.y * b.x; }

template<typename T> inline T dot_prod(vect2<T> &v1, vect2<T> &v2) { return v1.x * v2.x + v1.y * v2.y; }

template<typename T> inline T norm_sq(vect2<T> &_v) { return _v.x * _v.x + _v.y * _v.y; }

template<typename T>
point2<T> point2_translate(point2<T> p, vect2<ll> _v) { return {p.x + _v.x, p.y + _v.y}; }

template<typename T>
point2<ftype> point2_translate(point2<T> p, vect2<ftype> _v) { return {p.x + _v.x, p.y + _v.y}; }

template<typename T>
ftype dist2line(point2<T> p, point2<T> a, point2<T> b, point2<ftype> &c) {
  vect2<T> ap = get_mvec2(a, p), ab = get_mvec2(a, b);
  auto u = (ftype)dot_prod(ap, ab) / norm_sq(ab);
  c = point2_translate<T>(a, mvec2_scalar(ab, u));
  return hypot(p.x - c.x, p.y - c.y);
}

template<typename T>
ftype dist2segment(point2<T> p, point2<T> a, point2<T> b, point2<ftype> &c) {
  vect2<T> ap = get_mvec2(a, p), ab = get_mvec2(a, b);
  auto u = (ftype)dot_prod(ap, ab) / norm_sq(ab);
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

inline bool intersect_1d(ftype a, ftype b, ftype c, ftype d) {
  if (a > b) swap(a, b); if (c > d) swap(c, d);
  return max(a, c) <= min(b, d) + eps;
}

inline bool betw(ftype l, ftype r, ftype x) { return min(l, r) <= x + eps and x <= max(l, r) + eps; }

template<typename T> bool segment_intersect(point2<T> a, point2<T> b, point2<T> c, point2<T> d, point2<ftype> &left, point2<ftype> &right) {
  if (!intersect_1d(a.x, b.x, c.x, d.x) or !intersect_1d(a.y, b.y, c.y, d.y)) return false;
  line2<ftype> n, m;
  line_equation(a, b, m); line_equation(c, d, n);
  ftype zn = det2(m.a, m.b, n.a, n.b);
  point2<ftype> tmp;
  if (abs(zn) < eps) {
    if (dist2line(c, a, b, tmp) > eps or dist2line(a, c, d, tmp) > eps) return false;
    if (b < a) swap(a, b);
    if (d < c) swap(c, d);
    left = max(a, c), right = min(b, d);
    return true;
  } else {
    left.x = right.x = -det2(m.c, m.b, n.c, n.b) / zn;
    left.y = right.y = -det2(m.a, m.c, n.a, n.c) / zn;
    return betw(a.x, b.x, left.x) and betw(a.y, b.y, left.y) and
           betw(c.x, d.x, left.x) and betw(c.y, d.y, left.y);
  }
}

template<typename T> double angle(point2<T> a, point2<T> o, point2<T> b) {
  auto oa = get_mvec2<T>(o, a), ob = get_mvec2<T>(o, b);
  return acos(dot_prod(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

template<typename T>
bool get_circle_center(point2<T> p1, point2<T> p2, ftype r, point2<ftype> &c) {
  // When need opposing center, swap points
  auto d2 = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  auto det = r * r / d2 - 0.25;
  if (det < 0.) return false;
  auto h = sqrt(det);
  c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
  c.y = (p1.y + p2.y) * 0.5 + (p1.x - p2.x) * h;
  return true;
}
