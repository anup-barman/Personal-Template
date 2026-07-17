const int N = 2e5 + 10;  // max string size
int len[N], lnk[N]{-1}, last, sz = 1;
unordered_map<char, int> to[N];
void add(char c) {
  int cur = sz++;
  len[cur] = len[last] + 1;
  int u = last;
  while (u != -1 and !to[u].count(c)) {
    to[u][c] = cur;
    u = lnk[u];
  }
  if (u == -1) {
    lnk[cur] = 0;
  } else {
    int v = to[u][c];
    if (len[v] == len[u] + 1) {
      lnk[cur] = v;
    } else {
      int w = sz++;
      len[w] = len[u] + 1, lnk[w] = lnk[v], to[w] = to[v];
      while (u != -1 and to[u][c] == v) {
        to[u][c] = w;
        u = lnk[u];
      }
      lnk[cur] = lnk[v] = w;
    }
  }
  last = cur;
}