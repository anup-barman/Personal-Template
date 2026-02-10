// using picks theorem
// interior = area - (boundary / 2) + 1
// 2 * interior = 2 * area - boundary + 2
void solve() {
  int n;
  cin >> n;
  pt p[n];
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  ll boundary = 0, area = 0;
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    pt diff = p[j] - p[i];
    boundary += gcd(diff.x, diff.y);
    area += p[i].cross(p[j]);
  }
  area = abs(area);
  ll interior = (area - boundary + 2) / 2;
  cout << interior << " " << boundary << "\n";
}