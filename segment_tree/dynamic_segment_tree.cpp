#include "bits/stdc++.h"

using namespace std;

using ll = long long;

struct node {
  int l, r;
  ll val;
  node() { l = r = -1; val = 0; }
};
int tree_size = 1;

array<node, 400000> tree;

void update(int node, int start, int end, int idx, ll val) {
  if (start == end) {
    tree[node].val = val;
    return;
  }
  int mid = (start + end) >> 1;
  if (idx <= mid) {
    if (tree[node].l < 0) tree[node].l = tree_size++;
    update(tree[node].l, start, mid, idx, val);
  } else {
    if (tree[node].r < 0) tree[node].r = tree_size++;
    update(tree[node].r, mid + 1, end, idx, val);
  }
  int idxl = tree[node].l, idxr = tree[node].r;
  auto vl = idxl != -1 ? tree[idxl].val : 0;
  auto vr = idxr != -1 ? tree[idxr].val : 0;
  tree[node].val = vl + vr;
}

ll query(int node, int start, int end, int l, int r) {
  if (node == -1) return 0;
  if (end < l or start > r) return 0;
  if (l <= start and end <= r) return tree[node].val;
  int mid = (start + end) >> 1;
  return query(tree[node].l, start, mid, l, r) + query(tree[node].r, mid + 1, end, l, r);
}
