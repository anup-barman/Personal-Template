ll max_subarray_sum(const vector<int>& nums) {
  if (nums.empty()) return 0;
  ll current_max = nums[0];
  ll global_max = nums[0];
  for (size_t i = 1; i < nums.size(); i++) {
    current_max = max((ll)nums[i], current_max + nums[i]);
    global_max = max(global_max, current_max);
  }
  return global_max;
}