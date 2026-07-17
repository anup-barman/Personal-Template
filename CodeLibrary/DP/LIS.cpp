void LIS(const vector<int>& nums) {
  int n = nums.size();
  if (n == 0) return;
  // parent[i] stores the index of the predecessor of nums[i] in the LIS
  vector<int> parent(n, -1);
  // tails_id[k] stores the index (in nums) of the smallest tail of all increasing subsequences of length k+1
  vector<int> tails_id;
  // tails_val[k] stores the actual value of that tail (helper for binary search)
  vector<int> tails_val;
  // DP Definition (Implicit in greedy approach):
  // L[i] = Length of the longest increasing subsequence ending at index i.
  // We don't store L[i] explicitly, but compute it on the fly using the 'tails' arrays.
  // Base Case:
  // The first element starts a subsequence of length 1.
  for (int i = 0; i < n; i++) {
    int x = nums[i];
    // Find the first element in tails_val that is >= x
    auto it = lower_bound(tails_val.begin(), tails_val.end(), x);
    int idx = it - tails_val.begin();
    // Transition:
    // If x extends the longest existing subsequence, append it.
    // Otherwise, replace the existing tail to maintain the "smallest ending value" property
    // which allows future elements to extend the list easier.
    // We also link nums[i] to the element currently ending the subsequence of length (idx).
    if (it == tails_val.end()) {
      tails_val.push_back(x);
      tails_id.push_back(i);
    } else {
      *it = x;
      tails_id[idx] = i;
    }
    // If we are extending a sequence of length > 0, the parent is the end of the previous length
    if (idx > 0) {
      parent[i] = tails_id[idx - 1];
    }
  }
  // Reconstruction
  int curr = tails_id.back();  // Index of the last element of the LIS
  vector<int> lis_path;
  while (curr != -1) {
    lis_path.push_back(nums[curr]);
    curr = parent[curr];
  }
  reverse(lis_path.begin(), lis_path.end());
  // Output
  cout << "LIS Length: " << lis_path.size() << endl;
  for (int x : lis_path) cout << x << " ";
  cout << endl;
}