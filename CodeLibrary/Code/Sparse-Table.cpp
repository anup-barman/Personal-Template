const int MAXN = 2e5 + 10;
const int K = 26;

int n, arr[MX], spt[25][MX];
int log2Floor(int i) {
  return 31 - __builtin_clz(i);
}
void build() {
  int k = log2Floor(n);
  copy(arr, arr + n, spt[0]);
  for (int i = 1; i <= k; ++i) {
    for (int j = 0; j + (1 << i) <= n; j++) {
      spt[i][j] = min(spt[i - 1][j], spt[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int query(int l, int r) {
  int i = log2Floor(r - l + 1);
  return min(spt[i][l], spt[i][r - (1 << i) + 1]);
}