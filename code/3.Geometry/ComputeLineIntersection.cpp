/**
 * Description: compute intersection of line passing through $a$ and $b$ with line passing through $c$ and $d$, assuming that unique intersection exists; for segment intersection, check if segments intersect first.
 */
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
  b=b-a; d=c-d; c=c-a;
  assert(dot(b, b) > EPS && dot(d, d) > EPS);
  return a + b*cross(c, d)/cross(b, d);
}