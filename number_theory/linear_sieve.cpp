#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> linear_sieve(int n) {
  vector<int> spf(n + 1), prime_set;

  for (int i = 2; i <= n; ++i) {
    if (!spf[i]) {
      prime_set.push_back(i);
      spf[i] = i;
    }

    for (int j = 0; (long long)i * prime_set[j] <= n; ++j) {
      spf[i * prime_set[j]] = prime_set[j];
      if (i % prime_set[j] == 0)
        break;
    }
  }

  return { prime_set, spf }; // 0: prime numbers, 1: spf
}
