// the given points needs to be adjacent
void polygonArea() {
  int n;
  cin >> n;
  P p[n];
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  ll area = 0;
  for (int i = 0; i < n; ++i) {
    // calculating wrt the origin
    area += p[i].cross(p[(i + 1) % n]);
  }
  cout << abs(area) << "\n";
}