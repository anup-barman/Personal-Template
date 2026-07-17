// XOR from 0 to x
int fx(int x) {
  if (x % 4 == 0) return x;
  if (x % 4 == 1) return 1;
  if (x % 4 == 2) return x + 1;
  return 0; // x % 4 == 3
}
int rangeXOR(int l, int r) {
  return fx(r) ^ fx(l - 1);
}
