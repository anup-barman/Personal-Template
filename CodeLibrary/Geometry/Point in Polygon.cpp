bool segmentContains(pt a, pt b, pt c) {
  if (a.cross(b, c) != 0) {
    return false;
  }
  return (min(a.x, b.x) <= c.x and c.x <= max(a.x, b.x)) and (min(a.y, b.y) <= c.y and c.y <= max(a.y, b.y));
}
void solve() {
  int n;
  cin >> n;
  pt p[n];
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  int q;
  cin >> q;
  while (q--) {
    pt temp;
    cin >> temp;

    int cnt = 0;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
      int j = (i + 1) % n;

      if (segmentContains(p[i], p[j], temp)) {
        flag = true;
        break;
      }

      pt l, r;
      if (p[i].x <= p[j].x) {
        l = p[i];
        r = p[j];
      } else {
        l = p[j];
        r = p[i];
      }

      if (temp.cross(l, r) < 0) {
        if (l.x <= temp.x and temp.x < r.x) {
          cnt++;
        }
      }
    }

    if (flag) {
      cout << "BOUNDARY\n";
    } else if (cnt % 2 == 0) {
      cout << "OUTSIDE\n";
    } else {
      cout << "INSIDE\n";
    }
  }
}