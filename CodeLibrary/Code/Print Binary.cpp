void printBin(ll n) {
  int msb = 63 - __builtin_clzll(n);
  for (int i = msb; i >= 0; i--) {
    cout << ((n >> i) & 1);
  }
  cout << "\n";
}