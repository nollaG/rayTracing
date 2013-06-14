#include "inc/GFlat.h"


GFlat::GFlat(){}
GFlat::GFlat(const GVector3& normal,const GVector3& point):
  m_Normal(normal),m_Point(point){}
void GFlat::setNormal(const GVector3& normal) {
  m_Normal=normal;
}

void GFlat::setPoint(const GVector3& point) {
  m_Point = point;
}

GVector3 GFlat::getNormal() const {
  return m_Normal;
}
GVector3 GFlat::getPoint() const {
  return m_Point;
}
GVector3 GFlat::getNormal(const GVector3& v) const {
  return m_Normal;
}
INTERSECTION_TYPE GFlat::isIntersected(const Ray& ray,double& point) {
  double tmp1=m_Point*m_Normal - m_Normal*ray.getOrigin();
  double tmp2=m_Normal*ray.getDirection();
  double t=tmp1/tmp2;
  if (t<0)
    return MISS;
  if (point>t) {
    point = t;
    return INTERSECTED_OUT;
  }
  return MISS;
}
