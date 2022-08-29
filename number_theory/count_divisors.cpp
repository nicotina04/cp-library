/* Dont use. This code is not perfect */
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
  /*
  To Do
  check num is prime
  check sqrt(num) is prime
  else this is not a prime
  https://www.dropbox.com/s/ny5nx5swg8bueth/divisors.pdf?dl=0
  https://codeforces.com/blog/entry/22317?#comment-797506
  */
  return ret;
}
