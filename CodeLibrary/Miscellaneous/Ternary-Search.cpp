// Floating point
for (int i = 0; i < 100; ++i) {
  double m1 = l + (r - l) / 3.0;
  double m2 = r - (r - l) / 3.0;
  if (f(m1) < f(m2)) {
    l = m1; // The max is in [m1, r]
  } else {
    r = m2; // The max is in [l, m2]
  }
}
// Integers
int ternarySearchInt(int l, int r) {
  while (r - l > 2) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    
    if (f(m1) < f(m2)) {
      l = m1;
    } else {
      r = m2;
    }
  }
  // Manually check all remaining points
  int best_x = l;
  for (int i = l + 1; i <= r; ++i) {
    if (f(i) > f(best_x)) {
      best_x = i;
    }
  }
  return best_x;
}