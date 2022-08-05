#include "bits/stdc++.h"

using namespace std;

vector<int> buildsa(string &s) {
  int n = s.size(), m = max(256, n) + 1;
  vector<int> sa(n), r(n+n), nr(n+n), cnt(m), idx(n);
  iota(sa.begin(), sa.end(), 0);
  for(int i = 0; i < n; ++i) r[i] = s[i];

  auto csort = [&](int x) {
    for(int i=0;i<m;++i) cnt[i] = 0;
    for(int i=0;i<n;++i) cnt[r[i+x]]++;
    for(int i=1;i<m;++i) cnt[i] += cnt[i-1];
  };

  for(int d = 1; d < n; d <<= 1) {
    auto cmp = [&](int i,int j){
      return r[i]<r[j] || (r[i]==r[j] && r[i+d]<r[j+d]);
    };

    csort(d);
    for(int i=n-1;~i;--i) idx[--cnt[r[i+d]]] = i;
    csort(0);
    for(int i=n-1;~i;--i) sa[--cnt[r[idx[i]]]] = idx[i];

    nr[sa[0]] = 1;
    for(int i=1;i<n;++i) nr[sa[i]] = nr[sa[i-1]] + cmp(sa[i-1], sa[i]);
    for(int i=0;i<n;++i) r[i] = nr[i];

    if(r[sa[n-1]]==n) break;
  }
  return sa;
}

vector<int> buildlcp(string &s) {
  int n = s.size();
  vector<int> sa = buildsa(s), lcp(n), isa(n);
  for (int i = 0; i < n; ++i) isa[sa[i]] = i;
  for (int k=0, i=0; i < n; ++i) {
    if (!isa[i]) continue;
    for (int j = sa[isa[i]-1]; s[i+k]==s[j+k]; ++k);
    lcp[isa[i]] = (k ? k-- : 0);
  }
  return lcp;
}
