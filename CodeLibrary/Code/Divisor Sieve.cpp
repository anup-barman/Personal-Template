const int mxN = 1e5 + 10;
vector<int> divisors[mxN];
void divisorSeive() {
  for (int i = 1; i < mxN; i++) {
    for (int j = i; j < mxN; j += i) {
      divisors[j].push_back(i);
    }
  }
}
