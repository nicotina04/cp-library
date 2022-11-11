constexpr int MXN = 1e5+10;
int sub[MXN], depth[MXN], parent[MXN], top[MXN], in[MXN], out[MXN], num;
vector<int> al[MXN], tree[MXN];
void dfs_sub(int cur) {
  sub[cur] = 1;
  for (int &i : tree[cur]) {
    depth[i] = depth[cur] + 1;
    dfs_sub(i);
    sub[cur] += sub[i];
    if (sub[i] > sub[*begin(tree[cur])]) swap(i, *begin(tree[cur]));
  }
}
void euler_tour(int cur) {
  in[cur] = ++num;
  for (int i : tree[cur]) {
    top[i] = i == *begin(tree[cur]) ? top[cur] : i;
    euler_tour(i);
  }
  out[cur] = num;
}
ll query_hld(int a, int b) {
  auto ret = 0;
  while (top[a] != top[b]) {
    if (depth[top[a]] < depth[top[b]]) swap(a, b);
    int stt = top[a];
    // ret ?= query [in(stt), in(a)]
    a = parent[stt];
  }
  if (depth[a] > depth[b]) swap(a, b);
  // ret ?= query [in(a), in(b)]
  return ret;
}
