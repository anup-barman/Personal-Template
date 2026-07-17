const ll mod = 1e9;
vector<vector<ll>> matMul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
  ll row1 = a.size(), col1 = a[0].size();
  ll row2 = b.size(), col2 = b[0].size();
  vector<vector<ll>> res(row1, vector<ll>(col2, 0));
  for (ll i = 0; i < row1; i++) {
    for (ll j = 0; j < col1; j++) {
      for (ll k = 0; k < row2; k++) {
        res[i][j] = (res[i][j] + (1LL * a[i][k] * b[k][j]) % mod) % mod;
      }
    }
  }
  return res;
}
vector<vector<ll>> matExpo(vector<vector<ll>>& Mat, ll exp) {
  ll row = Mat.size(), col = Mat[0].size();
  ll p = row;
  vector<vector<ll>> res(p, vector<ll>(p, 0));
  for (ll i = 0; i < p; i++) res[i][i] = 1;
  while (exp) {
    if (exp & 1) res = matMul(res, Mat);
    Mat = matMul(Mat, Mat);
    exp >>= 1;
  }
  return res;
}
// b = (A(i), A(i-1), A(i-2), A(i-3))
// M = Magic matrix, nth = nth term, known = known value
ll get_nth(ll nth, ll known, vector<ll>& b, vector<vector<ll>>& M) {
  if (nth <= known) return b[nth - 1] % mod;
  reverse(b.begin(), b.end());
  vector<vector<ll>> me = matExpo(M, nth - known);  // MAT^(nth-known)
  ll ans = 0;
  for (int i = 0; i < known; i++) {
    ans = (ans + (b[i] * me[i][0]) % mod) % mod;
  }
  return ans;
}