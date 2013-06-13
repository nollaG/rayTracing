#ifndef GSPHERE_H
#define GSPHERE_H
#include "GVector3.h"
#include "Ray.h"
#include "GObject.h"

class GSphere:public GObject {
  private:
    GVector3 m_Center;
    float m_Radius;
  public:
    GSphere();
    GSphere(const GVector3&,float);
    void setCenter(const GVector3&);
    void setRadius(float);
    GVector3 getCenter() const;
    float getRadius() const;
    INTERSECTION_TYPE isIntersected(const Ray&,float&) const;
    GVector3 getNormal(const GVector3&) const;
};



#endif /* end of include guard: GSPHERE_H */

