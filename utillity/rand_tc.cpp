#include "bits/stdc++.h"

namespace rand_tc {
  template <typename T>
  vector<T> get_rand_seq(int num, T low, T high) {
    random_device rd;
    mt19937 generator(rd());
    vector<T> ret(num);
    uniform_int_distribution<T> dt(low, high);
    for (auto& i : ret) i = dt(generator);
    return ret;
  }
}
