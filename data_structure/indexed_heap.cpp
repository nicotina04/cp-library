#include "bits/stdc++.h"

using namespace std;

template <typename T>
struct idx_heap {
  struct Elem {
    int i;
    T w;
    bool operator < (const Elem &o) const {
      return w != o.w ? w < o.w : i < o.i;
    }
  };

  Elem *arr;
  int *pos;
  int size;

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
    auto k = arr[cur].w;
    arr[cur].w = w;
    k < w ? down(cur) : up(cur);
  }

  void up(int cur) {
    while (cur > 1) {
      if (arr[cur].w >= arr[cur / 2].w) break;
      swap(arr[cur], arr[cur / 2]);
      pos[arr[cur].i] = cur;
      cur /= 2;
    }
    pos[arr[cur].i] = cur;
  }

  void down(int cur) {
    while (cur * 2 <= size) {
      int mx;
      if (cur * 2 == size or arr[cur * 2].w < arr[cur * 2 + 1].w) mx = cur * 2;
      else mx = cur * 2 + 1;
      if (arr[cur].w <= arr[mx].w) break;
      swap(arr[cur], arr[mx]);
      pos[arr[cur].i] = cur;
      cur = mx;
    }
    pos[arr[cur].i] = cur;
  }

  T pop() {
    T ret = arr[1].i;
    arr[1] = arr[size--];
    pos[arr[1].i] = 1;
    down(1);
    return ret;
  }

  void del(int i) {
    int cur = pos[i];
    T k = arr[cur].w;
    arr[cur] = arr[size--];
    pos[arr[cur].i] = cur;
    k < arr[cur].w ? down(cur) : up(cur);
  }
};
