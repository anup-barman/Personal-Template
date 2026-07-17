// SOD = ((P^(x+1)-1)/(P-1)) * ((Q^(y+1)-1)/(Q-1)) * ((R^(z+1)-1)/(R-1))
// NOD = P^x * Q^y * R^z  => here, P, Q, R are prime factors & x, y, z are
// powers NOD = (x + 1) (y + 1) (z + 1)
pair<int, int> SOD_NOD(int n) {
  int sod = 1, nod = 1;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      int pown = 1, pows = 0;
      while (n % i == 0) {
        pown *= i;  // p^e
        pows++;
        n /= i;
      }
      pown *= i;                    // p^e+1
      sod *= (pown - 1) / (i - 1);  //(p^e+1)-1 / p-1
      nod *= (pows + 1);
    }
  }
  if (n > 1) {
    sod *= (n + 1);
    nod *= 2;
  }
  return {sod, nod};
}
