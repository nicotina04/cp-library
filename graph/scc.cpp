#include <bits/stdc++.h>

using namespace std;

#define NODE_MAX 100001
int discovered[NODE_MAX];
bool finished[NODE_MAX];
vector<int> al[NODE_MAX];
stack<int> s;
int cnt;
vector<vector<int>> scc;
int dfs(int cur) {
  int parent = discovered[cur] = cnt++;
  s.push(cur);    
  for (int i: al[cur]) {
    if (discovered[i] == -1) parent = min(parent, dfs(i)); // CARE: init val == -1
    else if (!finished[i]) parent = min(parent, discovered[i]);
  }
  if (parent == discovered[cur]) {
    vector<int> group;
    while (true) {
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
