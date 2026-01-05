class stree {
  vector<int> seg, lazy;
public:
  segtree(int n) {
    seg.resize(4 * n + 5);
    lazy.resize(4 * n + 5);
  }
  void propagate(int i, int low, int high) {
    if (lazy[i] != 0) {
      seg[i] += (high - low + 1) * lazy[i];
      if (low != high) {
        lazy[2 * i + 1] += lazy[i];
        lazy[2 * i + 2] += lazy[i];
      }
      lazy[i] = 0;
    }
  }
  void build(int i, int low, int high, int arr[]) {
    if (low == high) {
      seg[i] = arr[low];
      return;
    }
    int mid = (low + high) >> 1;
    build(2 * i + 1, low, mid, arr);
    build(2 * i + 2, mid + 1, high, arr);
    seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
  }
  void update(int i, int low, int high, int l, int r, int val) {
    propagate(i, low, high);
    if (high < l or r < low) return;
    if (low >= l and high <= r) {
      seg[i] += (high - low + 1) * val;
      if (low != high) {
        // has children
        lazy[2 * i + 1] += val;
        lazy[2 * i + 2] += val;
      }
      return;
    }
    int mid = (low + high) >> 1;
    update(2 * i + 1, low, mid, l, r, val);
    update(2 * i + 2, mid + 1, high, l, r, val);
    seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
  }
  int query(int i, int low, int high, int l, int r) {
    propagate(i, low, high);
    if (high < l or r < low) return 0;
    if (low >= l and high <= r) return seg[i];
    int mid = (low + high) >> 1;
    int left = query(2 * i + 1, low, mid, l, r);
    int right = query(2 * i + 2, mid + 1, high, l, r);
    return left + right;
  }
};