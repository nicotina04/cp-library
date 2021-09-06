#include <bits/stdc++.h>

using namespace std;

#define NODE_MAX 501
vector<pair<int, int>> graph[NODE_MAX];
long long dist[NODE_MAX];
int node_cnt[NODE_MAX];
bool inq[NODE_MAX];

bool spfa(int start, int limit) {
  queue<int> q;
  fill(dist, dist + NODE_MAX, 1e18);
  dist[start] = 0;
  inq[start] = 1;
  ++node_cnt[start];
  q.push(start);
  while (q.size()) {
    int cur = q.front();
    q.pop();
    inq[cur] = 0;
    for (auto &node: graph[cur]) {
      int nv = node.first, w = node.second;
      if (dist[cur] + w < dist[nv]) {
        dist[nv] = dist[cur] + w;
        if (!inq[nv]) {
          if (++node_cnt[nv] >= limit) return false;
          inq[nv] = 1;
          q.push(nv);
        }
      }
    }
  }
  return true;
}
