int n;
const int MX = 2e3 + 5;
const int inf = 2e9;

vector<int> adj[MX];

int prim() {
  int total_weight = 0;
  vector<bool> selected(n, false);
  // min_w[i] stores the minimum weight to reach node i
  vector<int> min_w(n, inf);
  // par[i] stores the node that connects to i (previously min_e[i].to)
  vector<int> par(n, -1);
  min_w[0] = 0;
  for (int i = 0; i < n; ++i) {
    int u = -1;  // u is the Source node we are selecting
    // Find the unselected node with the smallest min_w
    for (int j = 0; j < n; ++j) {
      if (!selected[j] and (u == -1 || min_w[j] < min_w[u])) {
        u = j;
      }
    }
    if (min_w[u] == inf) {
      cout << "No MST!" << "\n";
      exit(0);
    }
    selected[u] = true;
    total_weight += min_w[u];
    // Print edge (u and the node that connected to it)
    if (par[u] != -1) {
      cout << u << " " << par[u] << "\n";
    }
    // Update neighbors
    // v is the Destination node (neighbor)
    for (int v = 0; v < n; ++v) {
      // Check if edge u -> v is shorter than v's current best weight
      if (adj[u][v] < min_w[v]) {
        min_w[v] = adj[u][v];
        par[v] = u;  // Store that we reached v from u
      }
    }
  }
  return total_weight;
}