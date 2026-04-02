//number of occourence of word in a text
const ll N = 1e6+10, A = 26;
ll trie[N][A], pos[N], slink[N], dp[N], tot = 1;
vector<int> order;
void initTrie(){
  order.clear();
  while(tot--){
    memset(trie[tot], 0, sizeof(trie[tot]));
  }
  memset(pos, 0, sizeof(pos));
  memset(slink, 0, sizeof(slink));
  memset(dp, 0, sizeof(dp)); tot = 1;
}
void addStr(string &s, int ind){
  ll u = 0;
  for(auto it: s){
    ll n = it-'a';
    if(trie[u][n]==0) trie[u][n] = tot++;
    u = trie[u][n];
  } pos[ind] = u;
}
void build(){
  queue<ll> q; q.push(0);
  while(!q.empty()){
    ll p = q.front(); q.pop();
    order.push_back(p);
    for(ll c = 0; c<A; c++){
      ll u = trie[p][c];
      if(!u) continue;
      q.push(u);
      if(!p) continue;
      ll v = slink[p];
      while(v && !trie[v][c]) v = slink[v];
      slink[u] = trie[v][c];
    }
  }
}
void trav(string &s){
  ll u = 0;
  for(char c: s){
    c-='a';
    while(u && !trie[u][c]) u = slink[u];
    u = trie[u][c]; dp[u]++;
  }
  reverse(order.begin(), order.end());
  for(auto u: order){
    dp[slink[u]]+=dp[u];
  }
}
void solve(){
  ll n; cin>>n;
  string text; cin>>text;
  string s;
  for(ll i = 0; i<n; i++){
    cin>>s; addStr(s, i);
  }
  build(); trav(text);
  for(ll i = 0; i<n; i++){
    cout<<dp[pos[i]]<<endl;
  }
}
int32_t main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll tc = 1;
  cin>>tc;
  for(ll i = 1; i<=tc;i++){
    cout<<"Case "<<i<<": \n";
    initTrie();
    solve();
  }
}
