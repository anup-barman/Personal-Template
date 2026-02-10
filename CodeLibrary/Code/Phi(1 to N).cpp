const int MX = 1e7 + 10;
int phi[MX];
void sieve() {
  for (int i = 0; i < MX; i++) phi[i] = i;
  for (int i = 2; i < MX; i++) {
    if (phi[i] == i) {
      for (int j = i; j < MX; j += i) {
        phi[j] -= phi[j] / i;
      }
    }
  }
}