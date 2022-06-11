#include "bits/stdc++.h"

using namespace std;

#define RANGE_MAX 200001
vector<int> tree[RANGE_MAX * 4];
int ar[RANGE_MAX];

int mid(int s, int e) { return s + (e - s) / 2; }
void init(int node, int start, int end)
{
  vector<int> &cur = tree[node];
  if (start == end)
  {
    cur.push_back(ar[start]);
    return;
  }
  int m = mid(start, end);
  init(node * 2, start, m);
  init(node * 2 + 1, m + 1, end);
  vector<int> &l = tree[node * 2], &r = tree[node * 2 + 1];
  cur.resize(l.size() + r.size());
  merge(l.begin(), l.end(), r.begin(), r.end(), cur.begin());
}

int query(int node, int start, int end, int l, int r, int val)
{
  if (end < l || start > r) return 0;
  vector<int> &cur = tree[node];
  if (l <= start && end <= r) // Edit below line when need other query
    return upper_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
  int m = mid(start, end);
  return query(node * 2, start, m, l, r, val) + query(node * 2 + 1, m + 1, end, l, r, val);
}
