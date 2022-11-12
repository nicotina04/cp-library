#include <bits/stdc++.h>

using namespace std;

constexpr int MXLOG = 22, MXN = 1e6+10;
int spas[MXLOG][MXN];
int h[MXN];
void do_spas() {
  for (int i = 1; i < MXLOG; ++i) {
    for (int j = 1; j < MXN; ++j) {
      spas[i][j] = spas[i - 1][spas[i - 1][j]];
    }
  }
}
int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  int diff = h[u] - h[v];
  for (int i = MXLOG - 1; i >= 0; i--)
    if (diff & (1 << i)) u = spas[u][i];
  if (u == v) return u;
  for (int i = MXLOG - 1; i >= 0; i--)
    if (spas[u][i] != spas[v][i])
      u = spas[u][i], v = spas[v][i];
  return spas[u][0];
}
