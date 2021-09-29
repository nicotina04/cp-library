#include <bits/stdc++.h>

#define BI_G 2001
bool visited[BI_G];
int bpt[BI_G];
vector<int> graph[BI_G];

int bi_match(int cur) {
  if (visited[cur]) return 0;
  visited[cur] = 1;
  for (int i: graph[cur]) {
    if (!bpt[i] || bi_match(i)) {
      bpt[i] = cur;
      return 1;
    }
  }
  return 0;
}
