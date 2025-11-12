/**
 * Description: Computes the area of a (possibly nonconvex) polygon, assuming that the coordinates are listed in a clockwise or counterclockwise fashion.
 */
double ComputeSignedArea(const vector<PT> &p) {
  double area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return area / 2.0;
}

double ComputeArea(const vector<PT> &p) {
  return fabs(ComputeSignedArea(p));
}
// integer area
void computeIntArea() {
	int n; cin >> n;
	point arr[n];
	for (int i = 0; i < n; i++) {
		arr[i].read();
	}
	point a = {0, 0};
	ll ans = 0;
	for (int i = 0; i + 1 < n; i++) {
		ans += a.triangle(arr[i], arr[i + 1]);
	}
	ans += a.triangle(arr[n - 1],	arr[0]);
	cout << abs(ans) << "\n";
}
