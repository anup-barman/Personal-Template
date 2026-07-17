//FULL MÖBIUS FUNCTION TEMPLATE
//Möbius Sieve (O(N log log N))
//Computes:
//mu[n] → Möbius value
//primes[] → list of primes
//isPrime[]
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int mu[MAXN + 1];
bool isPrime[MAXN + 1];
vector<int> primes;

void mobius_sieve() {
    for (int i = 1; i <= MAXN; i++)
      mu[i] = 1, isPrime[i] = true;
    for (int i = 2; i <= MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = i; j <= MAXN; j += i) {
                isPrime[j] = false;
                mu[j] *= -1;
            }
            long long sq = 1LL * i * i;
            if (sq <= MAXN) {
                for (int j = sq; j <= MAXN; j += sq)
                  mu[j] = 0;
            }
      }
    }
    mu[1] = 1;
}

//Count Numbers ≤ n Coprime with x
long long count_coprime(long long n, int x) {
    long long ans = 0;
    for (int d = 1; d * d <= x; d++) {
        if (x % d == 0) {
            ans += 1LL * mu[d] * (n / d);
            if (d != x / d)
               ans += 1LL * mu[x / d] * (n / (x / d));
      }
    }
    return ans;
}
//Count Pairs (i, j) with gcd(i, j) = 1 (1 ≤ i,j ≤ n)

long long count_coprime_pairs(int n) {
    long long ans = 0;
    for (int d = 1; d <= n; d++) {
      long long t = n / d;
      ans += 1LL * mu[d] * t * t;
    }
    return ans;
}


//Count Coprime Pairs in an Array (ICPC CLASSIC)
//Problem:
//Count (i,j) such that gcd(a[i], a[j]) = 1.
long long count_array_coprime_pairs(vector<int>& a) {
    int maxA = *max_element(a.begin(), a.end());
    vector<int> cnt(maxA + 1, 0);

    for (int x : a)
      cnt[x]++;

    vector<int> freq(maxA + 1, 0);
    for (int i = 1; i <= maxA; i++) {
      for (int j = i; j <= maxA; j += i)
      freq[i] += cnt[j];
    }
    long long ans = 0;
    for (int d = 1; d <= maxA; d++) {
      if (mu[d] != 0)
          ans += 1LL * mu[d] * freq[d] * (freq[d] - 1) / 2;
    }
    return ans;
}

//Mobius Inversion (Template)

vector<long long> mobius_inversion(vector<long long>& f, int n) {
    vector<long long> g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j += i) {
        g[j] += mu[i] * f[j / i];
      }
    }
    return g;
}

//When to Use This Template
//Use Möbius when problem mentions:
//gcd = 1
//coprime pairs
//divisor sums
//inclusion–exclusion
//multiplicative functions

//Complexity Summary
//Task
//Time
//Sieve
//O(N log log N)
//Coprime count
//O(√x)
//Pair counting
//O(N)
//Array coprime
//O(A log A)


//Contest Tips (IMPORTANT)
//Always precompute μ once
//Combine with prefix sums
//Watch out for overflow
//μ values are only {-1, 0, +1}