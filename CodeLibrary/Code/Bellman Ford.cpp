#define ll long long
#define INF 1e18

void solve() {
  int n, m, v;
  cin >> n >> m >> v;  // n = nodes, m = edges, v = source (0-indexed)

  vector<array<ll, 3>> edges(m);  // each edge: {a, b, cost}
  for (int i = 0; i < m; i++) cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

  vector<ll> d(n, INF);
  vector<int> p(n, -1);
  d[v] = 0;

  int x = -1;
  for (int i = 0; i < n; i++) {
    x = -1;
    for (auto& e : edges) {
      int a = e[0], b = e[1];
      ll cost = e[2];
      if (d[a] < INF && d[b] > d[a] + cost) {
        d[b] = max(-INF, d[a] + cost);
        p[b] = a;
        x = b;
      }
    }
  }

  if (x == -1) {
    cout << "No negative cycle from vertex " << v << '\n';
    return;
  }

  int y = x;
  for (int i = 0; i < n; i++) y = p[y];

  vector<int> path;
  for (int cur = y;; cur = p[cur]) {
    path.push_back(cur);
    if (cur == y && path.size() > 1) break;
  }
  reverse(path.begin(), path.end());

  cout << "Negative cycle: ";
  for (int u : path) cout << u << ' ';
  cout << '\n';
}