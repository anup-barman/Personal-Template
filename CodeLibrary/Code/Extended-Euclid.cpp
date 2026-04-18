// It finds integers x and y (coefficients) such that: ax + by = gcd(a, b)
int extendedGCD(int a, int b, int& x, int& y) {
  // Base Case
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int x1, y1;
  int g = extendedGCD(b % a, a, x1, y1);
  // Update x and y using results of recursive call
  x = y1 - (b / a) * x1;
  y = x1;
  return g;
}