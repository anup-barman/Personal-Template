int lucas(int n, int r) {
  int ans = 1;
  while (n > 0 or r > 0) {
    ans = ans * 1LL * nCr(n % M, r % M) % M;
    n /= M, r /= M;
  }
  return ans;
}