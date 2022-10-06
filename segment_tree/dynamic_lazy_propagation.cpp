#include "bits/stdc++.h"

using namespace std;

using ll = long long;

#define MAXN 200001

struct node {
  ll sum, lazy;
  int l, r;
  node() { sum = lazy = 0, l = r = -1; }
};

int tree_size = 1;
array<node, MAXN*64> tree;

inline int get_mid(int ss, int ee) { return ss + (ee - ss) / 2; }

void push(int node, int start, int end) {
  if (node == -1) return;
  auto &lz = tree[node].lazy;
  if (!lz) return;
  tree[node].sum += lz * (end - start + 1);
  if (start != end) {
    int &ptrl = tree[node].l, &ptrr = tree[node].r;
    if (ptrl == -1) ptrl = tree_size++;
    if (ptrr == -1) ptrr = tree_size++;
    tree[ptrl].lazy += lz;
    tree[ptrr].lazy += lz;
  }
  lz = 0;
}

void add(int node, int start, int end, int l, int r, ll val) {
  push(node, start, end);
  if (node == -1 or start > r or end < l) return;
  if (l <= start and end <= r) {
    tree[node].lazy += val;
    push(node, start, end);
    return;
  }
  int mid = get_mid(start, end);
  int &ptrl = tree[node].l, &ptrr = tree[node].r;
  if (ptrl == -1) ptrl = tree_size++;
  if (ptrr == -1) ptrr = tree_size++;
  add(ptrl, start, mid, l, r, val);
  add(ptrr, mid + 1, end, l, r, val);
  auto lval = tree[ptrl].sum;
  auto rval = tree[ptrr].sum;
  tree[node].sum = lval + rval;
}

ll sum(int node, int start, int end, int l, int r) {
  if (node == -1 or start > r or end < l) return 0;
  push(node, start, end);
  if (l <= start and end <= r) return tree[node].sum;
  int mid = get_mid(start, end);
  return sum(tree[node].l, start, mid, l, r) + sum(tree[node].r, mid + 1, end, l, r);
}
