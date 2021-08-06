/*
Author: nicotina04

Segment tree with lazy propagation (Segment sum form)
*/
#include <bits/stdc++.h>

using namespace std;

inline int mid(int s, int e) { return s + (e - s) / 2; }

template <typename T>
class lazy_segtree
{
private:
  vector<T> lazy, tree;
public:
  lazy_segtree(int n): lazy(n * 4), tree(n * 4) { init(1, 1, n); }

  T init(int node, int start, int end)
  {
    if (start == end) return tree[node] = ar[end];
    int m = mid(start, end);
    return tree[node] = init(node * 2, start, m) + init(node * 2 + 1, m + 1, end);
  }

  void propa(int node, int start, int end)
  {
    if (!lazy[node]) return;

    tree[node] += (end - start + 1) * lazy[node];

    if (start != end)
      lazy[node * 2] += lazy[node], lazy[node * 2 + 1] += lazy[node];

    lazy[node] = 0;
  }

  void add(int node, int start, int end, int l, int r, T val)
  {
    propa(node, start, end);
  
    if (start > r || end < l) return;

    if (l <= start && end <= r)
    {
      lazy[node] += val;
      propa(node, start, end);

      if (start != end)
      {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
      }

      return;
    }

    int m = mid(start, end);
    add(node * 2, start, m, l, r, val);
    add(node * 2 + 1, m + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  T sum(int node, int start, int end, int l, int r)
  {
    propa(node, start, end);
    if (start > r || end < l) return 0;
    if (l <= start && end <= r) return tree[node];

    int m = mid(start, end);
    return sum(node * 2, start, m, l, r) + sum(node * 2 + 1, m + 1, end, l, r);
  }
};
