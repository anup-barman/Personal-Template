vector<pt> convexHull(vector<pt> p) {
  sort(p.begin(), p.end());
  vector<pt> hull;
  for (int rep = 0; rep < 2; ++rep) {
    const int S = hull.size();
    for (pt c : p) {
      while ((int)hull.size() - S >= 2) {
        pt a = hull.end()[-2];
        pt b = hull.end()[-1];
        if (a.cross(b, c) <= 0) {
          // b is on the left of c, it is valid
          break;
        }
        hull.pop_back();  // remove b
      }
      hull.push_back(c);
    }
    hull.pop_back();
    reverse(p.begin(), p.end());
  }
  return hull;
}