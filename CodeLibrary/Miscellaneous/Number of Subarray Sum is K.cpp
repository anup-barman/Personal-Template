//write gpHashTable code before this part
void solution(){ 
int n, k; cin >> n >> k;
int total_sum = 0;
vector < int > pre(n + 7, 0);
for (int i = 1; i <= n; i++) {
  int temp; cin >> temp;
  total_sum += temp;
  if (i == 1) pre[i] = temp;
  else pre[i] = pre[i - 1] + temp; }
int cnt_subarry = 0;
gp_hash_table < int, int, customHash> table;
table[0] = 1;
for (int i = 1; i <= n; i++) {
  cnt_subarry += table[pre[i] - k];
  table[pre[i]]++;
} cout << cnt_subarry << endl; }
