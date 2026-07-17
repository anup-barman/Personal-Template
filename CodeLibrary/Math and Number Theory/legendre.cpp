// returns power of prime p in n!
long long legendre(long long n, long long p) {
    long long ans = 0;
    while (n > 0) {
        n /= p;
        ans += n;
    }
    return ans;
}
