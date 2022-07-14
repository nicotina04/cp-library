vector<int> bake_pi(string &pat) {
  int sz = pat.size();
  vector<int> ret(sz);

  int j = 0;
  for (int i = 1; i < sz; i++) {
    while (j and pat[i] != pat[j]) j = ret[j - 1];
    if (pat[j] == pat[i]) ret[i] = ++j;
  }

  return ret;
}

vector<int> kmp(string &target, string &pat) {
  vector<int> ret;
  auto pi = bake_pi(pat);

  int j = 0;
  for (int i = 0; i < target.size(); i++) {
    while (j and target[i] != pat[j]) j = pi[j - 1];
    if (target[i] != pat[j]) continue;
    if (j == pat.size() - 1) {
      ret.push_back(i - j);
      j = pi[j];
    } else {
      ++j;
    }
  }
  return ret;
}
