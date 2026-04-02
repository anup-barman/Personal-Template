/*a[i] <= 1e6
for all 1<=g<=n, how many pairs exist such that g = gcd(a[i], a[j]);
complexity : nlogn
*/
ll n; cin >> n;
ll a[n + 1];
ll cnt[n + 1]; memset(cnt, 0, sizeof cnt);
for (ll i = 1; i <= n; i++) {cin >> a[i]; cnt[a[i]]++;}
ll gcd[n + 1]; memset(gcd, 0, sizeof gcd);
for (ll i = n; i >= 1; i--) {
	ll pair = 0, invalid_pair = 0;
	for (ll j = i; j <= n; j += i) {
		pair += cnt[j];
		invalid_pair += gcd[j];}
	pair = (pair * (pair - 1)) / 2;
	gcd[i] = pair - invalid_pair;
	// how many pairs exist whose gcd is i 
}
