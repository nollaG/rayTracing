#ifndef GSPHERE_H
#define GSPHERE_H
#include "GVector3.h"
#include "Ray.h"
#include "GObject.h"

class GSphere:public GObject {
  private:
    GVector3 m_Center;
    double m_Radius;
  public:
    GSphere();
    GSphere(const GVector3&,double);
    void setCenter(const GVector3&);
    void setRadius(double);
    GVector3 getCenter() const;
    double getRadius() const;
    INTERSECTION_TYPE isIntersected(const Ray&,double&) const;
    GVector3 getNormal(const GVector3&) const;
};



#endif /* end of include guard: GSPHERE_H */

