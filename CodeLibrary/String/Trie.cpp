const ll N = 1e6 + 5, A = 26;
ll trie[N][A], cnt[N], tot = 1, root = 1;
void initTrie() {
  cnt[tot] = 0;
  root = 1;
}
void addStr(string& s) {
  ll u = 1;
  for (auto it : s) {
    ll n = it - 'a';
    if (trie[u][n] == 0) {
      trie[u][n] = ++tot;
    }
    u = trie[u][n];
    cnt[u]++;
  }
}
ll wordCount(string& s) {
  ll u = 1;
  for (auto it : s) {
    int n = it - 'a';
    if (trie[u][n] == 0) return 0;
    u = trie[u][n];
  }
  return cnt[u];
}
