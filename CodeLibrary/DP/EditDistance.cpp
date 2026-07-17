int edit_distance(string s1, string s2) {
  int m = s1.size(), n = s2.size();
  // DP: dp[i][j] = min ops to convert s1[0...i-1] to s2[0...j-1]
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
  // Base: Converting empty string to s2 requires j inserts (and vice versa)
  for (int i = 0; i <= m; i++) dp[i][0] = i;
  for (int j = 0; j <= n; j++) dp[0][j] = j;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        // Trans: 1 + min(Delete, Insert, Replace)
        dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
      }
    }
  }
  return dp[m][n];
}