bool lineLineIntersection(P p1, P p2, P p3, P p4) {
  if ((p2 - p1).cross((p4 - p3)) == 0) {
    // lines are parallel
    // basically the slopes of two lines are same, producing the cross product 0
    if (p1.cross(p2, p3) != 0) {
      // lines are not collinear
      return false;
    }
    // bounding box idea, 2 lines are collinear but not intersecting
    for (int rep = 0; rep < 2; ++rep) {
      if (max(p1.x, p2.x) < min(p3.x, p4.x) or max(p1.y, p2.y) < min(p3.y, p4.y)) {
        return false;
      }
      swap(p1, p3), swap(p2, p4);
    }
    // lines are collinear and intersecting
    return true;
  }
  // lines are not parallel
  for (int rep = 0; rep < 2; ++rep) {
    ll cp1 = p1.cross(p2, p3);
    ll cp2 = p1.cross(p2, p4);
    if ((cp1 < 0 and cp2 < 0) or (cp1 > 0 and cp2 > 0)) {
      // lines are not intersecting
      return false;
    }
    swap(p1, p3), swap(p2, p4);
  }
  // lines are intersecting
  return true;
}