const int N = 1e5 + 5, INF = 1e18 + 7;
vector<pair<int, int>> g[N];
bool visited[N];
vector<int> dist(N, INF), parent(N);
bool dijkstra(int source) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, source});
  dist[source] = 0;
  parent[source] = -1;
  while (pq.size()) {
    int x = pq.top().second;
    pq.pop();
    if (visited[x]) continue;
    visited[x] = 1;
    for (auto [child_x, child_wt] : g[x]) {
      if (dist[x] + child_wt < dist[child_x]) {
        parent[child_x] = x;
        dist[child_x] = child_wt + dist[x];
        pq.push({dist[child_x], child_x});
      }
    }
  }
  return (dist[n] == INF);
}
