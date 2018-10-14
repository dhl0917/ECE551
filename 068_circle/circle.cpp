#include "circle.h"

#include <math.h>
#define pi 3.1415926

Circle::Circle(Point c, double r) : center(c), radius(r) {}
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double area = 0.0;
  double d = center.distanceFrom(otherCircle.center);
  double r1 = radius;
  double r2 = otherCircle.radius;
  if (d >= r1 + r2) {
    area = 0.0;
    return area;
  }
  if (d <= r2 - r1) {
    area = pi * r1 * r1;
    return area;
  }
  if (d <= r1 - r2) {
    area = pi * r2 * r2;
    return area;
  }
  else {
    double theta1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
    double theta2 = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
    double s1 = ((2 * theta1) / (2 * pi)) * pi * r1 * r1;
    double s2 = ((2 * theta2) / (2 * pi)) * pi * r2 * r2;
    double s3 = 2 * r1 * sin(theta1) * d / 2;
    area = s1 + s2 - s3;
    return area;
  }
}
