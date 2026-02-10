// pal[1][i] = longest odd (half rounded down) palindrome around pos i and
// starts at i - pal[1][i] and ends at i + pal[1][i] pal[0][i] = half length of
// longest even palindrome around pos i, i + 1 and starts at i - par[0][i] + 1
// and ends at i + pal[0][i]
const int N = 5e5 + 10;
int pal[2][N];
void manacher(string& s) {
  int n = s.size(), idx = 2;
  while (idx--) {
    for (int l = -1, r = -1, i = 0; i < n - 1; ++i) {
      if (i > r)
        l = r = i;
      else {
        int k = min(r - i, pal[idx][l + r - i]);
        l = i - k, r = i + k;
      }
      while (l - idx >= 0 and r + 1 < n and s[l - idx] == s[r + 1]) l--, r++;
      pal[idx][i] = r - i;
      // [l - 1 + idx : r] palindrome
    }
  }
}