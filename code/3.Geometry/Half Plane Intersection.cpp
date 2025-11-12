/**
 * Description: Calculates the intersection of halfplanes, assuming every half-plane allows the region to the left of its line.
 */

struct Halfplane {
  PT p, pq; ld angle;

  Halfplane() {}
  // Two points on line
  Halfplane(const PT& a, const PT& b) : p(a), pq(b - a) {
    angle = atan2l(pq.y, pq.x);    
  }
  bool out(const PT& r) { 
    return cross(pq, r - p) < -EPS; 
  }
  bool operator < (const Halfplane& e) const { 
    return angle < e.angle;
  } 
  friend PT inter(const Halfplane& s, const Halfplane& t) {
    ld alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
    return s.p + (s.pq * alpha);
  }
};

vector<PT> hp_intersect(vector<Halfplane>& H) { 
  PT box[4] = {  // Bounding box in CCW order
    PT(INF, INF),  PT(-INF, INF), 
    PT(-INF, -INF), PT(INF, -INF) 
  };

  for(int i = 0; i<4; i++) { // Add bounding box half-planes.
      Halfplane aux(box[i], box[(i+1) % 4]);
      H.push_back(aux);
  }

  sort(H.begin(), H.end());
  deque<Halfplane> dq; int len = 0;
  for(int i = 0; i < int(H.size()); i++) {
    while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
      dq.pop_back(); --len;
    }
    while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
      dq.pop_front(); --len;
    }
    if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < EPS) {
      if (dot(H[i].pq, dq[len-1].pq) < 0.0)
        return vector<PT>();
      if (H[i].out(dq[len-1].p)) {
        dq.pop_back(); --len;
      }
      else continue;
    }
    dq.push_back(H[i]); ++len;
  }

  while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
    dq.pop_back(); --len;
  }
  while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
    dq.pop_front(); --len;
  }

  // Report empty intersection if necessary
  if (len < 3) return vector<PT>();

  // Reconstruct the convex polygon from the remaining half-planes.
  vector<PT> ret(len);
  for(int i = 0; i+1 < len; i++) {
    ret[i] = inter(dq[i], dq[i+1]);
  }
  ret.back() = inter(dq[len-1], dq[0]);
  return ret;
}