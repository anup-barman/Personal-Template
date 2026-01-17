struct Dinic {
  struct Edge {
    int to;
    ll capacity;
    int rev;  // index of reverse edge
  };

  vector<vector<Edge>> adj;
  vector<int> level;
  vector<int> ptr;
  int n;

  Dinic(int nodes) : n(nodes), adj(nodes), level(nodes), ptr(nodes) {}

  void add_edge(int from, int to, ll cap) {
    adj[from].push_back({to, cap, (int)adj[to].size()});
    adj[to].push_back({from, 0, (int)adj[from].size() - 1});
  }

  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto& edge : adj[v]) {
        if (edge.capacity > 0 && level[edge.to] == -1) {
          level[edge.to] = level[v] + 1;
          q.push(edge.to);
        }
      }
    }
    return level[t] != -1;
  }

  ll dfs(int v, int t, ll pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
      auto& edge = adj[v][cid];
      int tr = edge.to;
      if (level[v] + 1 != level[tr] || edge.capacity == 0) continue;
      ll tr_pushed = dfs(tr, t, min(pushed, edge.capacity));
      if (tr_pushed == 0) continue;
      edge.capacity -= tr_pushed;
      adj[tr][edge.rev].capacity += tr_pushed;
      return tr_pushed;
    }
    return 0;
  }

  ll max_flow(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) {
      fill(ptr.begin(), ptr.end(), 0);
      while (ll pushed = dfs(s, t, 1e18)) {
        flow += pushed;
      }
    }
    return flow;
  }
};
// Usage in int main():
int n, m;
cin >> n >> m;
Dinic dinic(n + 1); // Initialize with N+1 nodes (0 to N)
for (int i = 0; i < m; i++) {
    int u, v; ll cap;
    cin >> u >> v >> cap;
    // Add directed edge u -> v with capacity
    // For bidirectional, add edge v -> u as well
    dinic.add_edge(u, v, cap); 
}
// Compute flow from node 1 (Source) to node n (Sink)
cout << dinic.max_flow(1, n) << endl;