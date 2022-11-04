#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 100001;
int discovered[MAXN];
bool finished[MAXN];
vector<int> al[MAXN];
stack<int> s;
int cnt;
vector<vector<int>> scc;
int dfs(int cur) {
  int parent = discovered[cur] = cnt++;
  s.push(cur);
  for (int &i : al[cur]) {
    if (discovered[i] == -1) parent = min(parent, dfs(i)); // CARE: init value is -1
    else if (!finished[i]) parent = min(parent, discovered[i]);
  }
  if (parent == discovered[cur]) {
    vector<int> group;
    while (1) {
      int t = s.top();
      s.pop();
      group.push_back(t);
      finished[t] = true;
      if (t == cur) break;
    }
    scc.push_back(group);
  }
  return parent;
}
