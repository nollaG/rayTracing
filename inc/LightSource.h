#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include "GObject.h"
#include "GVector3.h"

class LightSource {
  protected:
    GVector3 m_Position;
    GVector3 m_Ka;//ambient
    GVector3 m_Kd;//diffuse
    GVector3 m_Ks;//Specular
  public:
    LightSource();
    LightSource(const GVector3& pos,const GVector3& ka,const GVector3& kd,const GVector3& ks);
    void setPosition(const GVector3&);
    void setKa(const GVector3&);
    void setKd(const GVector3&);
    void setKs(const GVector3&);
    GVector3 getPosition() const;
    GVector3 getKa() const;
    GVector3 getKd() const;
    GVector3 getKs() const;
    virtual GVector3 calAmbient(const GVector3& material_Ka) const=0;
    virtual GVector3 calDiffuse(const GVector3& material_Kd,const GVector3& normal,const GVector3& rayDirection) const =0;
    virtual GVector3 calSpecular(const GVector3& material_Ks,const GVector3& normal,const GVector3& rayDirection,const GVector3& cameraDirection,double material_shinness) const=0;
    virtual GVector3 calColor(const GObject* obj,const GVector3& point,const GVector3& cameraPosition) const=0;
    virtual GVector3 getLightDirection(const GVector3& point) const=0;

};



#endif /* end of include guard: LIGHTSOURCE_H */

