#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "LightSource.h"
#include "GObject.h"
#include "GVector3.h"

class DirectionalLight:public LightSource {
  private:
    GVector3 m_Direction;
  public:
    DirectionalLight();
    DirectionalLight(const GVector3& dir);
    void setDirection(const GVector3& dir);
    GVector3 getDirection() const;
    GVector3 calAmbient(const GVector3& material_Ka) const;
    GVector3 calDiffuse(const GVector3& material_Kd,const GVector3& normal,const GVector3& rayDirection) const;
    GVector3 calSpecular(const GVector3& material_Ks,const GVector3& normal,const GVector3& rayDirection,const GVector3& cameraDirection,double material_shinness) const;
    GVector3 calColor(const GObject* obj,const GVector3& point,const GVector3& cameraPosition) const;
    GVector3 getLightDirection(const GVector3& point) const;
};

#endif /* end of include guard: DIRECTIONALLIGHT_H */

