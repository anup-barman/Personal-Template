string S;
ll memo[20][2][180];

ll dp(int idx, bool tight, int current_sum) {
  // DP Definition:
  // dp(idx, tight, current_sum) returns the count of valid suffixes we can form
  // starting from index 'idx', given the 'tight' constraint and the current state (sum).
  // Base Case: We have placed digits for all positions
  if (idx == S.size()) {
    return 1;  // Found 1 valid number (or check: return current_sum == target ? 1 : 0)
  }
  ll &ans = memo[idx][tight][current_sum];
  if (ans != -1) {
    return ans;
  }
  ll ans = 0;
  // Determine the upper bound for the current digit
  int limit = tight ? (S[idx] - '0') : 9;
  for (int digit = 0; digit <= limit; digit++) {
    // Transition:
    // Move to next index (idx + 1).
    // New tight constraint: (tight && (digit == limit))
    // New state: Update current_sum (or other state variable)
    bool next_tight = tight && (digit == limit);
    // Example logic: filtering or constraints go here
    // if (digit == 4) continue; // Example: skip digit 4
    ans += dp(idx + 1, next_tight, current_sum + digit);
  }
  return memo[idx][tight][current_sum] = ans;
}
// Wrapper function to query for range [0, N]
ll query(ll N) {
  if (N < 0) return 0;
  if (N == 0) return 1;  // Handling 0 case if needed
  S = to_string(N);
  memset(memo, -1, sizeof(memo));
  // Start from index 0, tight constraint is initially TRUE, initial sum is 0
  return dp(0, true, 0);
}
// To get answer for range [L, R]: query(R) - query(L - 1)