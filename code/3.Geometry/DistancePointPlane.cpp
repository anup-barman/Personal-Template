/**
 * Description: compute distance between point $(x,y,z)$ and plane $ax+by+cz=d$
 */
double DistancePointPlane(double x, double y, double z, double a, double b, double c, double d) {
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}