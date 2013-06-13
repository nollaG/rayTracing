#ifndef GFLAT_H
#define GFLAT_H
#include "GVector3.h"
#include "Ray.h"
#include "GObject.h"

class GFlat:public GObject{
  private:
    GVector3 m_Normal;
    GVector3 m_Point;
  public:
    GFlat();
    GFlat(const GVector3& normal,const GVector3& point);
    void setNormal(const GVector3&);
    void setPoint(const GVector3&);
    GVector3 getNormal() const;
    GVector3 getPoint() const;
    GVector3 getNormal(const GVector3&) const;
    INTERSECTION_TYPE isIntersected(const Ray&,float&) const;

};



#endif /* end of include guard: GFLAT_H */

