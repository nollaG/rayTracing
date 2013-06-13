#include "inc/GSphere.h"
#include <cmath>


GSphere::GSphere():m_Radius(0.0f){};
GSphere::GSphere(const GVector3& c,double r):m_Center(c),m_Radius(r){};
void GSphere::setCenter(const GVector3& c)
{
  m_Center=c;
}
void GSphere::setRadius(double f) {
  m_Radius=f;
}
GVector3 GSphere::getCenter() const {
  return m_Center;
}
double GSphere::getRadius() const {
  return m_Radius;
}

INTERSECTION_TYPE GSphere::isIntersected(const Ray& ray,double& dis) const {
  double A = ray.getDirection()*ray.getDirection(); //assuming 1.0f
  double B = ray.getDirection()*(ray.getOrigin()-this->m_Center)*2.0f;
  double C = (ray.getOrigin()-this->m_Center)*(ray.getOrigin()-this->m_Center)-this->m_Radius*this->m_Radius;
  double deta = B*B - 4*A*C;
  INTERSECTION_TYPE result = MISS;
  if (deta < 0) {
    return MISS;
  }
  deta = sqrt(deta);
  double x1 = (-B - deta) / 2.0f;
  double x2 = (-B + deta) / 2.0f;
  if (x2 > 0) {
    if (x1 < 0) {
      if (x2 < dis) {
        dis=x2;
        result = INTERSECTED_IN;
      }
    } else {
      if (x1 < dis) {
        dis = x1;
        result = INTERSECTED_OUT;
      }
    }
  }
  return result;
}

GVector3 GSphere::getNormal(const GVector3& v) const {
  return v-m_Center;
}
