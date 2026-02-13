#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Maximum limits as per problem statement
const int MAXN = 200005;
const int MAXK = 1000005;
const int INF = 1e9;

// Global variables to store graph and state
struct Edge {
  int to;
  int length;
};

vector<Edge> adj[MAXN];
bool removed[MAXN];      // To mark removed centroids
int subtree_size[MAXN];  // To calculate subtree sizes
int min_edges[MAXK];     // Lookup table: min edges for distance 'd'
int result = INF;        // Global best answer
int K_target;            // The target path length K

// DFS to calculate subtree sizes
void get_subtree_sizes(int u, int p) {
  subtree_size[u] = 1;
  for (auto& e : adj[u]) {
    if (e.to != p && !removed[e.to]) {
      get_subtree_sizes(e.to, u);
      subtree_size[u] += subtree_size[e.to];
    }
  }
}

// DFS to find the centroid
int find_centroid(int u, int p, int total_nodes) {
  for (auto& e : adj[u]) {
    if (e.to != p && !removed[e.to] && subtree_size[e.to] > total_nodes / 2) {
      return find_centroid(e.to, u, total_nodes);
    }
  }
  return u;
}

// Structure to temporarily store path info during DFS
struct PathInfo {
  int dist;
  int edges;
};

// DFS to collect all paths from the current subtree
void get_paths(int u, int p, int current_dist, int current_edges, vector<PathInfo>& paths) {
  if (current_dist > K_target) return;  // Optimization: Don't go deeper if K is exceeded

  paths.push_back({current_dist, current_edges});

  for (auto& e : adj[u]) {
    if (e.to != p && !removed[e.to]) {
      get_paths(e.to, u, current_dist + e.length, current_edges + 1, paths);
    }
  }
}

// Main decomposition function
void decompose(int u) {
  // 1. Calculate subtree sizes and find the centroid
  get_subtree_sizes(u, -1);
  int total_nodes = subtree_size[u];
  int centroid = find_centroid(u, -1, total_nodes);

  // 2. Process paths passing through the centroid
  // We use a list to keep track of modified indices to reset min_edges efficiently
  vector<int> modified_indices;
  min_edges[0] = 0;  // Base case: path of length 0 at centroid has 0 edges
  modified_indices.push_back(0);

  // Iterate over all children of the centroid
  for (auto& e : adj[centroid]) {
    if (removed[e.to]) continue;

    // Collect all paths from this child's subtree
    vector<PathInfo> child_paths;
    get_paths(e.to, centroid, e.length, 1, child_paths);

    // PHASE 1: QUERY
    // Check if any path in this subtree can match with a path from previous subtrees
    for (auto& p : child_paths) {
      if (K_target - p.dist >= 0) {
        // If the complementary distance exists in min_edges
        if (min_edges[K_target - p.dist] != INF) {
          result = min(result, min_edges[K_target - p.dist] + p.edges);
        }
      }
    }

    // PHASE 2: UPDATE
    // Add these paths to the global min_edges array for the next children to use
    for (auto& p : child_paths) {
      if (p.dist <= K_target) {
        if (min_edges[p.dist] == INF) {
          // If this is the first time we see this distance, record it to reset later
          modified_indices.push_back(p.dist);
          min_edges[p.dist] = p.edges;
        } else {
          // Update if we found a path with fewer edges
          min_edges[p.dist] = min(min_edges[p.dist], p.edges);
        }
      }
    }
  }

  // 3. Clean up: Reset min_edges array for the parent recursion
  for (int idx : modified_indices) {
    min_edges[idx] = INF;
  }

  // 4. Recurse: Remove centroid and decompose subtrees
  removed[centroid] = true;
  for (auto& e : adj[centroid]) {
    if (!removed[e.to]) {
      decompose(e.to);
    }
  }
}

// Function signature matching the IOI requirement
int best_path(int N, int K, int H[][2], int L[]) {
  // Initialization
  K_target = K;
  result = INF;
  for (int i = 0; i < N; i++) {
    adj[i].clear();
    removed[i] = false;
  }
  // Initialize min_edges with INF
  for (int i = 0; i <= K; i++) {
    min_edges[i] = INF;
  }

  // Build the graph
  for (int i = 0; i < N - 1; i++) {
    int u = H[i][0];
    int v = H[i][1];
    int w = L[i];
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  // Start Centroid Decomposition
  decompose(0);

  // Return result
  if (result == INF) return -1;
  return result;
}