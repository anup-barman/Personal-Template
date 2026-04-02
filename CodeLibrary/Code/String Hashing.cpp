const int mod1 = 911382323, mod2 = 972663749, b1 = 137, b2 = 139;
const int mxN = 5000010;
int pow_b1[mxN], pow_b2[mxN], inv_b1[mxN], inv_b2[mxN];
int binExp(int base, int power, int mod) {
  int res = 1;
  while (power) {
    if (power & 1) res = (1LL * res * base) % mod;
    base = (1LL * base * base) % mod;
    power >>= 1;
  }
  return res;
}
void pre() {
  pow_b1[0] = pow_b2[0] = 1;
  for (int i = 1; i < mxN; i++) {
    pow_b1[i] = (1LL * pow_b1[i - 1] * b1) % mod1;
    pow_b2[i] = (1LL * pow_b2[i - 1] * b2) % mod2;
  }
  inv_b1[mxN - 1] = binExp(pow_b1[mxN - 1], mod1 - 2, mod1);
  inv_b2[mxN - 1] = binExp(pow_b2[mxN - 1], mod2 - 2, mod2);
  for (int i = mxN - 2; i >= 0; i--) {
    inv_b1[i] = (1LL * inv_b1[i + 1] * b1) % mod1;
    inv_b2[i] = (1LL * inv_b2[i + 1] * b2) % mod2;
  }
}
vector<pair<int, int>> getPref(string& s) {
  int qq = s.size();
  vector<pair<int, int>> hsh(qq);
  for (int i = 0; i < qq; i++) {
    if (i == 0) {
      hsh[i].first = (1LL * s[i] * pow_b1[i]) % mod1;
      hsh[i].second = (1LL * s[i] * pow_b2[i]) % mod2;
    } else {
      hsh[i].first =
          (hsh[i - 1].first + (1LL * s[i] * pow_b1[i]) % mod1) % mod1;
      hsh[i].second =
          (hsh[i - 1].second + (1LL * s[i] * pow_b2[i]) % mod2) % mod2;
    }
  }
  return hsh;
}
pair<int, int> getHash(string& str) {
  int hsh1 = 0, hsh2 = 0, sz = str.size();
  for (int i = 0; i < sz; ++i) {
    hsh1 = (hsh1 + 1LL * str[i] * pow_b1[i] % mod1) % mod1;
  }
  for (int i = 0; i < sz; ++i) {
    hsh2 = (hsh2 + 1LL * str[i] * pow_b2[i] % mod2) % mod2;
  }
  return {hsh1, hsh2};
}
pair<int, int> getSub(int l, int r, vector<pair<int, int>>& v) {
  pair<int, int> q;
  if (l == 0) {
    q = {v[r].first, v[r].second};
  } else {
    int x = (1LL * ((v[r].first - v[l - 1].first + mod1) % mod1) * inv_b1[l]) %
            mod1;
    int y =
        (1LL * ((v[r].second - v[l - 1].second + mod2) % mod2) * inv_b2[l]) %
        mod2;
    q = {x, y};
  }
  return q;
}
