#include "bits/stdc++.h"

namespace rand_tc {
  using uid = uniform_int_distribution<long long>;
  using rdev = random_device;
  void print_rand_seq(int num, long long low, long long high, int iter = 1) {
    rdev rd;
    mt19937_64 generator(rd());
    auto dt = uid(low, high);
    cout << num << '\n';
    for (int i = 0; i < iter; i++) {
      for (int j = 0; j < num; j++) {
        cout << dt(generator) << ' ';
      }
      cout << '\n';
    }
  }
  void print_rand_graph(int nodes, int edges) {
    rdev rd;
    mt19937_64 generator(rd());
    auto dt = uid(1, nodes);
    cout << nodes << ' ' << edges << '\n';
    for (int i = 0; i < edges; i++) cout << dt(generator) << ' ' << dt(generator) << '\n';
  }
  void print_rand_graph_weight(int nodes, int edges, long long min_w, long long max_w) {
    rdev rd;
    mt19937_64 generator(rd());
    auto dt = uid(1, nodes);
    auto dt2 = uid(min_w, max_w);
    for (int i = 0; i < edges; i++)
      cout << dt(generator) << ' ' << dt(generator) << ' ' << dt2(generator) << '\n';
  }
}
