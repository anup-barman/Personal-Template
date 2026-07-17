vector<bool> vis(n + 1, false);
for(int i = 1; i <= n; i++){
    if(vis[i]) continue;
    vector<int> cycle;
    int cur = i;
    while(!vis[cur]){
        vis[cur] = true;
        cycle.push_back(cur);
        cur = p[cur];
    }
    // cycle contains one cycle
}