const int MX = 1e5 + 10;
vector<int> lst[MX];

vector<int> topSort(int n) {
  int in[n]{};
  for (int u = 0; u < n; ++u) {
    for (int v : lst[u]) {
      in[v]++;
    }
  }
  queue<int> q;
  for (int u = 0; u < n; ++u) {
    if (in[u] == 0) {
      q.push(u);
    }
  }
  vector<int> order;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.push_back(u);
    for (int v : lst[u]) {
      in[v]--;
      if (in[v] == 0) {
        q.push(v);
      }
    }
  }
  // If the topological sort doesn't contain all nodes, there is a cycle.
  if (order.size() < n) {
    return {};  // Return empty to indicate cycle
  }
  return order;
}