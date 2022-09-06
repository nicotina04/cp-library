int rt;

struct query
{
  int l, r, order;
  bool operator < (const query &arg) const
  {
    int x = r / rt, y = arg.r / rt;
    return x == y ? l < arg.l : x < y;
  }
};

void operation(int idx, bool yes)
{
  // Do something you want
}
