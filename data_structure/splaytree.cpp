template<typename T, typename U>
class splay_tree {
private:
  struct node {
    node *l, *r, *p;
    T key;
    U lazy, sum;
    int cnt;
    bool inv;
    node(T x, node *_p): l(nullptr), r(nullptr), p(_p), key(x), inv(0), cnt(1) {}
    node() { node(0, nullptr); }
    ~node() { delete l; delete r; }
  };
  void update(node *x) {
    x->cnt = 1;
    x->sum = x->key;
    if (x->l) {
      x->cnt += x->l->cnt;
      x->sum += x->l->sum;
    }
    if (x->r) {
      x->cnt += x->r->cnt;
      x->sum += x->r->sum;
    }
  }
  void rotate(node *x) {
    auto p = x->p;
    push(p);
    push(x);
    node *b = nullptr;
    if (!p) return;
    if (x == p->l) {
      p->l = b = x->r;
      x->r = p;
    } else {
      p->r = b = x->l;
      x->l = p;
    }
    x->p = p->p;
    p->p = x;
    if (b) b->p = p;
    (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
    update(p), update(x);
  }
public:
  node *root;
  // node *ptr[300005]; for range query
  splay_tree(): root(nullptr) {}
  void splay(node *x, node *g = nullptr) {
    while (x->p != g) {
      auto p = x->p;
      if (p->p == g) {
        rotate(x);
        break;
      }
      auto pp = p->p;
      ((p->l == x) == (pp->l == p) ? rotate(p) : rotate(x));
      rotate(x);
    }
    if (!g) root = x;
  }
  void insert(T key) {
    node *p = root, **pp;
    if (!p) {
      root = new node(key, nullptr);
      return;
    }
    while (1) {
      if (key == p->key) return;
      if (key < p->key) {
        if (!p->l) {
          pp = &p->l;
          break;
        }
        p = p->l;
      } else {
        if (!p->r) {
          pp = &p->r;
          break;
        }
        p = p->r;
      }
    }
    *pp = new node(key, p);
    splay(*pp);
  }
  bool find(T key) {
    node *p = root;
    if (!p) return false;
    while (p) {
      if (p->key == key) break;
      if (key < p->key) {
        if (!p->l) break;
        p = p->l;
      } else {
        if (!p->r) break;
        p = p->r;
      }
    }
    splay(p);
    return p->key == key;
  }
  bool erase(T key) {
    if (!find(key)) return false;
    node *p = root;
    if (p->l && p->r) {
      root = p->l;
      root->p = nullptr;
      node *x = root;
      while (x->r) x = x->r;
      x->r = p->r, p->r->p = x;
      delete p;
    } else if (p->l) {
      root = p->l;
      root->p = nullptr;
    } else if (p->r) {
      root = p->r;
      root->p = nullptr;
    } else {
      delete p;
      root = nullptr;
    }
    return true;
  }
  void kth(int k) {
    auto x = root;
    push(x); // Can change to inv
    while (1) {
      while (x->l && x->l->cnt > k) {
        x = x->l;
        push(x);
      }
      if (x->l) k -= x->l->cnt;
      if (!k--) break;
      x = x->r;
      push(x);
    }
    splay(x);
  }
  void add(int l, int r, T e) {
    auto tmp = interval(l, r);
    tmp->sum += e * tmp->cnt;
    tmp->lazy += e;
  }
  node* interval(int s, int e) {
    kth(e + 1);
    auto tmp = root;
    kth(s - 1);
    splay(tmp, root);
    return root->r->l;
  }
  void push(node *x) { // 1. segment mode
    x->key += x->lazy;
    if (x->l) {
      x->l->lazy += x->lazy;
      x->l->sum += x->l->cnt * x->lazy;
    }
    if (x->r) {
      x->r->lazy += x->lazy;
      x->r->sum += x->r->cnt * x->lazy;
    }
    x->lazy = 0;
  }
  void push_inv(node *x) { // 2. inversion mode
    if (!x->inv) return;
    swap(x->l, x->r);
    if (x->l) x->l->inv ^= 1;
    if (x->r) x->r->inv ^= 1;
    x->inv = 0;
  }
  void flip(int l, int r) {
    auto tmp = interval(l, r);
    tmp->inv ^= 1;
    splay(tmp);
  }
  void init(int n) {
    if (root) delete root;
    node *x;
    auto limit = numeric_limits<T>::min();
    root = x = new node(limit, nullptr);
    // ptr[0] = root;
    for (int i = 1; i <= n; ++i) {
      x->r = new node(i, x);
      x = x->r;
      // ptr[i] = x;
    }
    x->r = new node(-limit, x);
    while (n--) {
      update(x);
      x = x->p;
    }
    // ptr[n + 1] = x->r;
    // for (int i = n; i >= 1; --i) update(ptr[i]);
    // splay(ptr[n / 2]);
  }
};
