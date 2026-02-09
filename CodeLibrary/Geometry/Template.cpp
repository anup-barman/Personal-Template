struct P {
  ll x, y;
  friend istream& operator>>(istream& is, P& p) {
    return is >> p.x >> p.y;
  }
  friend ostream& operator<<(ostream& os, const P& p) {
    return os << p.x << " " << p.y;
  }
  P operator-(const P& other) const {
    return P(x - other.x, y - other.y);
  }
  void operator-=(const P& other) {
    x -= other.x;
    y -= other.y;
  }
  ll cross(const P& other) const {
    return x * other.y - y * other.x;
  }
  ll cross(const P& a, const P& b) const {
    return (a - *this).cross(b - *this);
  }
};