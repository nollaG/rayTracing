#ifndef GOBJECT_H

#define GOBJECT_H
#include "GVector3.h"
#include "Ray.h"

enum INTERSECTION_TYPE {INTERSECTED_IN=-1,MISS=0,INTERSECTED_OUT=1};

class GObject {
  private:
    GVector3 m_Ka;//ambient material
    GVector3 m_Kd;//diffuse material
    GVector3 m_Ks;//specular material
    float m_Shininess;
    float m_Reflectivity;
  public:
    GObject();
    GObject(const GVector3&,const GVector3&,const GVector3&,float,float);
    void setKa(const GVector3&);
    void setKd(const GVector3&);
    void setKs(const GVector3&);
    void setShininess(float);
    void setReflectivity(float);
    GVector3 getKa() const;
    GVector3 getKd() const;
    GVector3 getKs() const;
    float getShininess() const;
    float getReflectivity() const;
    virtual GVector3 getNormal() const=0;
    virtual INTERSECTION_TYPE isIntersected(const Ray&,float&) const=0;

};

#endif /* end of include guard: GOBJECT_H */
