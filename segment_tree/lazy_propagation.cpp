/*
Author: nicotina04

Segment tree with lazy propagation (Segment sum form)
*/
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class lazy_segtree {
private:
  vector<T> lazy, tree;
public:
  inline int mid(int s, int e) { return s + (e - s) / 2; }

  lazy_segtree(int _n): lazy(_n * 4), tree(_n * 4) {}

  T init(int node, int start, int end, int* _ar) {
    if (start == end) return tree[node] = _ar[end];
    int m = mid(start, end);
    return tree[node] = init(node * 2, start, m, _ar) + init(node * 2 + 1, m + 1, end, _ar);
  }

  void prop(int node, int start, int end) {
    if (!lazy[node]) return;
    tree[node] += (end - start + 1) * lazy[node];
    if (start ^ end)
      lazy[node * 2] += lazy[node], lazy[node * 2 + 1] += lazy[node];
    lazy[node] = 0;
  }

  void add(int node, int start, int end, int l, int r, T val) {
    prop(node, start, end);
    if (start > r || end < l) return;
    if (l <= start && end <= r) {
      lazy[node] += val;
      prop(node, start, end);
      return;
    }
    int m = mid(start, end);
    add(node * 2, start, m, l, r, val);
    add(node * 2 + 1, m + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  T sum(int node, int start, int end, int l, int r) {
    prop(node, start, end);
    if (start > r || end < l) return 0;
    if (l <= start && end <= r) return tree[node];
    int m = mid(start, end);
    return sum(node * 2, start, m, l, r) + sum(node * 2 + 1, m + 1, end, l, r);
  }
};
