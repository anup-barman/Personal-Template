class stree {
  vector<ll> st;

 public:
  stree(int n) {
    st.assign((n << 2) + 10, 0);
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
  ll query(int l, int r, int u, int s, int e) {
    if (e < l or r < s) return 0;
    if (l <= s and e <= r) return st[u];
    int v = u << 1, w = v | 1, m = (s + e) >> 1;
    return query(l, r, v, s, m) + query(l, r, w, m + 1, e);
  }
  void update(int i, int x, int u, int s, int e) {
    if (s == e) {
      st[u] = x;
      return;
    }
    int v = u << 1, w = v | 1, m = (s + e) >> 1;
    if (i <= m) update(i, x, v, s, m);
    else update(i, x, w, m + 1, e);
    st[u] = st[v] + st[w];
  }
};