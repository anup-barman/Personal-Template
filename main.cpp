#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

// Max H1 value is roughly 10^7 (half of 10^14)
// We need a sieve up to this value to factorize H1 quickly.
const int MAX_H1 = 10000005;
int spf[MAX_H1];  // Smallest Prime Factor

// Precompute smallest prime factors
void sieve() {
  for (int i = 0; i < MAX_H1; ++i) spf[i] = i;
  for (int i = 2; i * i < MAX_H1; ++i) {
    if (spf[i] == i) {
      for (int j = i * i; j < MAX_H1; j += i) {
        if (spf[j] == j) spf[j] = i;
      }
    }
  }
}

void solve(int t) {
  ll A, B;
  cin >> A >> B;

  string sB = to_string(B);
  string sA = to_string(A);
  int lenB = sB.length();
  int lenA = sA.length();

  // Strategy: Iterate lengths from Largest (lenB) down to Smallest (lenA)
  for (int len = lenB; len >= lenA; --len) {
    // Calculate split point
    // If len is odd (2r+1), H1 has r digits, H2 has r+1 digits.
    // If len is even (2r), H1 has r digits, H2 has r digits.
    int r = len / 2;
    int k = len - r;  // Length of second half

    // Calculate 10^k and 10^r safely
    ll powerOf10_k = 1;
    for (int i = 0; i < k; ++i) powerOf10_k *= 10;

    ll powerOf10_r = 1;
    for (int i = 0; i < r; ++i) powerOf10_r *= 10;  // Used to determine bounds of H1

    // Determine the Upper Bound for H1
    ll start_h1;
    if (len == lenB) {
      start_h1 = B / powerOf10_k;
    } else {
      // If length is less than B's length, max number is 99...9
      // Max H1 is the first r digits of 99...9
      start_h1 = powerOf10_r - 1;
    }

    // Determine the Lower Bound for H1
    ll min_h1;
    if (len == lenA) {
      min_h1 = A / powerOf10_k;
    } else {
      // If length is greater than A's length, min number is 10...0
      // Min H1 is 10^(r-1)
      min_h1 = powerOf10_r / 10;
    }

    // Greedy Search: Iterate H1 downwards
    for (ll h1 = start_h1; h1 >= min_h1; --h1) {
      if (h1 == 0) continue;  // First half cannot be zero
      if (h1 == 1) continue;  // 1 has no divisors > 1

      // Determine max allowed value for H2
      ll limit_h2;
      if (len == lenB && h1 == start_h1) {
        // If we are at the tight upper bound of B, H2 is restricted by B's suffix
        limit_h2 = B % powerOf10_k;
      } else {
        // Otherwise H2 can be anything up to 99...9 (length k)
        limit_h2 = powerOf10_k - 1;
      }

      // Find best H2: Largest number <= limit_h2 that shares a factor with h1
      ll best_h2 = -1;
      int temp = (int)h1;

      // Factorize H1 using SPF
      while (temp > 1) {
        int p = spf[temp];

        // We need largest multiple of p <= limit_h2
        if (limit_h2 >= p) {
          ll candidate = (limit_h2 / p) * p;
          if (candidate > best_h2) best_h2 = candidate;
        }

        // Divide out p completely
        while (temp % p == 0) temp /= p;
      }

      // If we found a valid H2 (must be non-zero)
      if (best_h2 > 0) {
        ll result = h1 * powerOf10_k + best_h2;

        // Final Check: Must be >= A (Lower bound check)
        if (result >= A) {
          cout << "Case " << t << ": " << result << "\n";
          return;  // Found the largest!
        }
      }
    }
  }

  cout << "Case " << t << ": impossible\n";
}

int main() {
  // Optimize I/O operations
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  sieve();

  int T;
  if (cin >> T) {
    for (int i = 1; i <= T; ++i) {
      solve(i);
    }
  }
  return 0;
}