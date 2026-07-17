// Calculate X when we know Y and P for X^2 ≡ Y (mod P) 
ll tonelli_shanks(ll Y, ll P) {
  if (Y == 0) return 0;
  if (P == 2) return Y % 2;
  // Euler's criterion: Check if Y is a quadratic residue
  if (modPow(Y, (P - 1) / 2, P) != 1) {
    return -1;
  }
  
  ll Q = P - 1;
  ll S = 0;
  while (Q % 2 == 0) {
    Q /= 2;
    S++;
  }
  
  ll z = 2;
  while (modPow(z, (P - 1) / 2, P) != P - 1) {
    z++;
  }
  
  ll M = S;
  ll c = modPow(z, Q, P);
  ll t = modPow(Y, Q, P);
  ll R = modPow(Y, (Q + 1) / 2, P);
  
  while (t != 0 && t != 1) {
    ll t2i = t;
    ll i = 0;
    for (i = 1; i < M; i++) {
        t2i = (t2i * t2i) % P;
        if (t2i == 1) break;
    }
    ll b = c;
    for (int j = 0; j < M - i - 1; j++) {
        b = (b * b) % P;
    }
    ll b2 = (b * b) % P;
    M = i;
    c = b2;
    t = (t * b2) % P;
    R = (R * b) % P;
  }
  return R;
}