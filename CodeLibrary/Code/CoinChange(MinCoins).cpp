const int INF = 1e9;
int min_coins(int target, vector<int>& coins) {
  // DP Definition: dp[i] = minimum coins needed to make value i
  vector<int> dp(target + 1, INF);
  // Base Case: 0 coins are needed to make value 0
  dp[0] = 0;
  for (int i = 1; i <= target; i++) {
    for (int c : coins) {
      if (i - c >= 0) {
        // Transition: Try taking coin 'c', adding 1 to the count of (i-c)
        dp[i] = min(dp[i], dp[i - c] + 1);
      }
    }
  }
  return (dp[target] == INF) ? -1 : dp[target];
}