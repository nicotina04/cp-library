#include <bits/stdc++.h>

#define BI_G 2001
bool visited[BI_G];
int bpt[BI_G];
vector<int> graph[BI_G];

int bi_match(int cur) {
  for (int i: graph[cur]) {
    if (visited[i]) continue;
    visited[i] = 1;
    if (!bpt[i] || bi_match(bpt[i])) {
      bpt[i] = cur;
      return 1;
    }
  }
  return 0;
}
