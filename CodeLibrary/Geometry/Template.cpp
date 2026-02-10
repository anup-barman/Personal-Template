struct pt {
  ll x, y;
  friend istream& operator>>(istream& is, pt& p) {
    return is >> p.x >> p.y;
  }
  friend ostream& operator<<(ostream& os, const pt& p) {
    return os << p.x << " " << p.y;
  }
  pt operator-(const pt& other) const {
    return {x - other.x, y - other.y};
  }
  void operator-=(const pt& other) {
    x -= other.x, y -= other.y;
  }
  bool operator<(const pt& b) {
    return make_pair(x, y) < make_pair(b.x, b.y);
  }
  ll cross(const pt& other) const {
    return x * other.y - y * other.x;
  }
  ll cross(const pt& a, const pt& b) const {
    return (a - *this).cross(b - *this);
  }
};