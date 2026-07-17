//write gpHashTable code before this part
void solution(){
int n, k; cin >> n >> k;
int total_sum = 0;
vector < int > pre(n + 7, 0);
for (int i = 1; i <= n; i++) {
  int temp; cin >> temp; 
  total_sum += temp;
  if (i == 1) pre[i] = temp;
  else pre[i] = pre[i - 1] + temp;
} 
if (total_sum < k) { 
  cout << "-1" << endl; return; 
}
if (total_sum == k) {
  cout << "0" << endl; return; 
}
int maximum_subSize = 0;
gp_hash_table < int, int, customHash> table;
for (int i = 1; i <= n; i++) {
  if (pre[i] >= k) {
    int subSUM = pre[i] - k;
    if (subSUM == 0){
      maximum_subSize = max(maximum_subSize, i);
    }
    else if (table[subSUM]) {
      int left = table[subSUM];
      int right = i; int subSize = right - left;
      maximum_subSize = max(subSize, maximum_subSize);
    }
  } if (!table[pre[i]]) table[pre[i]] = i;
} cout << maximum_subSize << endl; }
