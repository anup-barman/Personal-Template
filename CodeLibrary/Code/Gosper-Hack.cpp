// Generates a single level r from nCr
vector<int> gen(int n, int r) {
  vector<int> v;
  int mask = (1 << r) - 1;
  do {
    v.push_back(mask);
    int x = mask & -mask;
    int y = mask + x;
    mask = ((mask & ~y) / x >> 1) | y;
  } while (mask < (1 << n));
  return v;
}