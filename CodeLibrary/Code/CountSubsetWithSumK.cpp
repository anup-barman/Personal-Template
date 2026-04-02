int memo[105][10005];  // (N, Sum)
vector<int> nums;
int K;
int solve(int idx, int sum) {
  // DP: dp[idx][sum] = number of ways to complete the sum using suffix nums[idx...]
  // Base: End of array. Return 1 if sum matches K, else 0
  if (idx == nums.size()) {
    return sum == K;
  }
  if (memo[idx][sum] != -1) return memo[idx][sum];
  // Trans: Sum of ways (Include current element) + (Exclude current element)
  int take = (sum + nums[idx] <= K) ? solve(idx + 1, sum + nums[idx]) : 0;
  int skip = solve(idx + 1, sum);
  return memo[idx][sum] = take + skip;
}