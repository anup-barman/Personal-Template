string a, b, c;
ll dp[55][55][55];
ll lcs(ll i, ll j, ll k) {
  if (i == a.size() or j == b.size() or k == c.size()) return 0;
  if (dp[i][j][k] != -1) return dp[i][j][k];
  if (a[i] == b[j] and a[i] == c[k]) return 1 + lcs(i + 1, j + 1, k + 1);
  ll ans = 0;
  ans = max(ans, lcs(i, j , k + 1));
  ans = max(ans, lcs(i, j + 1 , k));
  ans = max(ans, lcs(i + 1, j, k));
  return dp[i][j][k] = ans;
}
