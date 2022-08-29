#include "bits/stdc++.h"
#include "ext/rope"

using namespace std;

using ll = long long;

#define SIEVE_SIZE 1000001
vector<int> primes;
bitset<SIEVE_SIZE> nop;

void sieve(int mx) {
  for (int i = 2; i <= mx; i++) {
    if (nop[i]) continue;
    primes.push_back(i);
    for (int j = i << 1; j <= mx; j += i) nop.set(j);
  }
}

ll count_divisors(ll num) {
  ll ret = 1;
  for (ll i : primes) {
    if (i * i * i > num) break;
    int cnt = 1;
    while (num % i == 0) num /= i, ++cnt;
    ret *= cnt;
  }
  if (!nop[num]) ret <<= 1;
  else {
    ll lo = 1, hi = num;
    bool good = false;
    while (lo <= hi) {
      auto mid = lo + (hi - lo) / 2;
      if (mid * mid == num) {
        good = true; // mid is prime
        break;
      }
      if (mid * mid < num) lo = mid + 1;
      else hi = mid - 1;
    }
    if (good) ret *= 3;
    else ret *= 4;
  }
  return ret;
}
