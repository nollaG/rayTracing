#include "inc/Ray.h"
#include "inc/GVector3.h"

Ray::Ray(const GVector3& ori,const GVector3& dir):origin(ori),direction(dir){
  direction.normalize();
}

void Ray::setOrigin(const GVector3& ori) {
  origin=ori;
}

void Ray::setDirection(const GVector3& dir) {
  direction=dir;
  direction.normalize();
}

GVector3 Ray::getOrigin() const {
  return origin;
}

GVector3 Ray::getDirection() const {
  return direction;
}

GVector3 Ray::getPoint(float f) const {
  if (direction.length()==0) {
    return direction;
  }
  return origin+direction*f;
}
