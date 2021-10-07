#include <bits/stdc++.h>

using namespace std;
using ll = long long;

using pil = pair<int, ll>;
using pli = pair<ll, int>;
#define NODE_MAX 20001
vector<pil> al[NODE_MAX];
ll dist[NODE_MAX];
void dijkstra(int start) {
  fill(dist, dist + NODE_MAX, 1e18);
  dist[start] = 0;
  priority_queue<pli, vector<pli>, greater<pli>> pq;
  pq.push({0, start});
  while (pq.size()) {
    auto cur = pq.top();
    ll fee = cur.first; int now = cur.second;
    pq.pop();
    if (fee > dist[now]) continue;
    for (auto i: al[now]) {
      int nxt = i.first;
      ll nfee = fee + i.second;
      if (nfee >= dist[nxt]) continue;
      pq.push({nfee, nxt});
      dist[nxt] = nfee;
    }
  }
}
