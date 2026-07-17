vector<int> lst[MX];
bool dead[MX];
int sz[MX];
void get_sz(int u, int p) {
  sz[u] = 1;
  for (int v : lst[u]) {
    if (v != p && !dead[v]) {
      get_sz(v, u);
      sz[u] += sz[v];
    }
  }
}
int find_cen(int u, int p, int tot) {
  for (int v : lst[u]) {
    if (v != p && !dead[v] && sz[v] > tot / 2) {
      return find_cen(v, u, tot);
    }
  }
  return u;
}
void calc(int cen) {
  // work on centroid here
}
void decomp(int u) {
  get_sz(u, -1);
  int tot = sz[u];
  int cen = find_cen(u, -1, tot);
  calc(cen);
  dead[cen] = true;
  for (int v : lst[cen]) {
    if (!dead[v]) {
      decomp(v);
    }
  }
}