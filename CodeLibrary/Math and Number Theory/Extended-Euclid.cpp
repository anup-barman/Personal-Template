// Finds the greatest common divisor of a and b.
// Also finds integers x and y such that: ax + by = gcd(a, b)
int extendedGCD(int a, int b, int& x, int& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int x1, y1;
  int g = extendedGCD(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return g;
}