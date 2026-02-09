void lineLineIntersection() {
  P p1, p2, p3, p4;
  cin >> p1 >> p2 >> p3 >> p4;
  if ((p2 - p1).cross((p4 - p3)) == 0) {
    // lines are parallel
    // basically the slopes of two lines are same, producing the cross product 0
    if (p1.cross(p2, p3) != 0) {
      // lines are not collinear
      cout << "NO\n";
      return;
    }
    // bounding box idea, 2 lines are collinear but not intersecting
    for (int rep = 0; rep < 2; ++rep) {
      if (max(p1.x, p2.x) < min(p3.x, p4.x) or max(p1.y, p2.y) < min(p3.y, p4.y)) {
        cout << "NO\n";
        return;
      }
      swap(p1, p3), swap(p2, p4);
    }
    // lines are collinear and intersecting
    cout << "YES\n";
    return;
  }
  // lines are not parallel
  for (int rep = 0; rep < 2; ++rep) {
    ll cp1 = p1.cross(p2, p3);
    ll cp2 = p1.cross(p2, p4);
    if ((cp1 < 0 and cp2 < 0) or (cp1 > 0 and cp2 > 0)) {
      // lines are not intersecting
      cout << "NO\n";
      return;
    }
    swap(p1, p3), swap(p2, p4);
  }
  // lines are intersecting
  cout << "YES\n";
}