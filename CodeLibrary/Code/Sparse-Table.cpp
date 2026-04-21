const int MX = 2e5 + 10;
const int LOG = 25;
int arr[MX], st[MX][LOG];

void build(int n) {
  for (int i = 0; i < n; ++i) {
    st[i][0] = arr[i];
  }

  for (int j = 1; j < LOG; ++j) {
    for (int i = 0; i + (1 << j) <= n; ++i) {
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}
int query(int l, int r) {
  int len = r - l + 1;
  int k = 31 - __builtin_popcount(len);
  return min(st[l][k], st[r - (1 << k) + 1][k]);
}