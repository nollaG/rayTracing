#ifndef RAY_H

#define RAY_H
#include "GVector3.h"

class Ray {
  private:
    GVector3 origin;
    GVector3 direction;
  public:
    Ray(const GVector3&,const GVector3&);
    void setOrigin(const GVector3&);
    void setDirection(const GVector3&);
    GVector3 getOrigin() const;
    GVector3 getDirection() const;
    GVector3 getPoint(float) const;
};

#endif /* end of include guard: RAY_H */
