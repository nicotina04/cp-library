#include "bits/stdc++.h"

using namespace std;

template <typename T> struct Elem {
  int i;
  T w;
  bool operator < (const Elem &o) const { return w != o.w ? w < o.w : i < o.i; }
  bool operator > (const Elem &o) const { return w != o.w ? w > o.w : i < o.i; }
  bool operator == (const Elem &o) const { return w == o.w; }
  bool operator <= (const Elem &o) const { return *this < o or *this == o; }
  bool operator >= (const Elem &o) const { return *this > o or *this == o; }
};

template <typename T> struct idx_heap {
  Elem<T> *arr;
  int *pos, size;

  idx_heap(int _n) : size(0) {
    arr = new Elem<T>[_n + 1];
    pos = new int[_n + 1];
  }

  ~idx_heap() {
    delete[] arr;
    delete[] pos;
  }

  void push(int i, T w) {
    arr[++size] = {i, w};
    pos[i] = size;
    up(size);
  }

  void change(int i, T w) {
    int cur = pos[i];
    auto k = arr[cur];
    arr[cur].w = w;
    k < arr[cur] ? down(cur) : up(cur);
  }

  void update(int i, T w) {
    int cur = pos[i];
    auto k = arr[cur];
    arr[cur].w += w;
    k < arr[cur] ? down(cur) : up(cur);
  }

  void up(int cur) {
    while (cur > 1) {
      if (arr[cur] >= arr[cur / 2]) break;
      swap(arr[cur], arr[cur / 2]);
      pos[arr[cur].i] = cur;
      cur >>= 1;
    }
    pos[arr[cur].i] = cur;
  }

  void down(int cur) {
    while (cur * 2 <= size) {
      int mx;
      if (cur * 2 == size or arr[cur * 2] < arr[cur * 2 + 1]) mx = cur * 2;
      else mx = cur * 2 + 1;
      if (arr[cur] <= arr[mx]) break;
      swap(arr[cur], arr[mx]);
      pos[arr[cur].i] = cur;
      cur = mx;
    }
    pos[arr[cur].i] = cur;
  }

  int pop() {
    int ret = arr[1].i;
    arr[1] = arr[size--];
    pos[arr[1].i] = 1;
    down(1);
    return ret;
  }

  void del(int i) {
    int cur = pos[i];
    auto k = arr[cur];
    arr[cur] = arr[size--];
    pos[arr[cur].i] = cur;
    k < arr[cur] ? down(cur) : up(cur);
  }
};
