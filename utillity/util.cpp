#include "bits/stdc++.h"

namespace rand_tc {
  mt19937 generator(random_device());

  template <typename T>
  vector<T> get_rand_seq(int num, T low, T high) {
    vector<T> ret(num);
    uniform_int_distribution<T> dt(low, high);
    for (auto& i : ret) i = dt(generator);
    return ret;
  }
}
