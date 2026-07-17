ll count_ways(int target, vector<int>& coins) {
  // DP Definition: dp[i] = number of ways to make value i using given coins
  vector<ll> dp(target + 1, 0);
  // Base Case: There is 1 way to make value 0 (by choosing nothing)
  dp[0] = 1;
  for (int c : coins) {  // Loop coins *outside* to count combinations (unordered)
    for (int i = c; i <= target; i++) {
      // Transition: Add ways to make the remainder (i - c)
      dp[i] += dp[i - c];
    }
  }
  return dp[target];
}