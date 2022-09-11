using ll = int_fast64_t;
using pll = pair<ll, ll>;

ll distance_sum_point_pairs(vector<pll> &target)
{
  ll ret = 0;
  ll sqx = 0, sqy = 0, sumx = 0, sumy = 0;

  int sz = target.size();
  for (int i = 0; i < sz; i++)
  {
    ll x = target[i].first, y = target[i].second;
    ret += sqx;
    ret -= (sumx<<1) * x;
    ret += i * x * x;

    sqx += x * x;
    sumx += x;

    ret += sqy;
    ret -= (sumy<<1) * y;
    ret += i * y * y;

    sqy += y * y;
    sumy += y;
  }

  return ret;
}
