#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> eea(ll a, ll b) {
  ll r0 = a, r1 = b, s0 = 1, s1 = 0, t0 = 0, t1 = 1;
  ll tmp = 0, q = 0;
  while (r1) {
    q = r0 / r1;
    tmp = r0, r0 = r1;
    r1 = tmp - r1 * q;
    tmp = s0, s0 = s1;
    s1 = tmp - s1 * q;
    tmp = t0, t0 = t1;
    t1 = tmp - t1 * q;
  }
  return {r0, s0, t0}; // equation
  // return {r1, s1, t1}; // root
}
