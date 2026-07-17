class stree {
  vector<ll> st, lazy;

 public:
  stree(int n) {
    st.assign((n << 2) + 10, 0);
    lazy.assign((n << 2) + 10, 0);
  }
  void push(int u, int s, int e) {
    if (!lazy[u]) return;
    st[u] += (e - s + 1) * 1LL * lazy[u];
    if (s != e) {
      int v = u << 1, w = v | 1, m = (s + e) >> 1;
      lazy[v] += lazy[u];
      lazy[w] += lazy[u];
    }
    lazy[u] = 0;
  }
  void build(int u, int s, int e, int arr[]) {
    if (s == e) {
      st[u] = arr[s];
      return;
    }
    int v = u << 1, w = v | 1, m = (s + e) >> 1;
    build(v, s, m, arr);
    build(w, m + 1, e, arr);
    st[u] = st[v] + st[w];
  }
  void update(int l, int r, int x, int u, int s, int e) {
    push(u, s, e);
    if (e < l or r < s) return;
    int v = u << 1, w = v | 1, m = (s + e) >> 1;
    if (l <= s and e <= r) {
      st[u] += (e - s + 1) * 1LL * x;
      if (s != e) {
        lazy[v] += x;
        lazy[w] += x;
      }
      return;
    }
    update(l, r, x, v, s, m);
    update(l, r, x, w, m + 1, e);
    st[u] = st[v] + st[w];
  }
  ll query(int l, int r, int u, int s, int e) {
    push(u, s, e);
    if (e < l or r < s) return 0;
    if (l <= s and e <= r) return st[u];
    int v = u << 1, w = v | 1, m = (s + e) >> 1;
    return query(l, r, v, s, m) + query(l, r, w, m + 1, e);
  }
};