#include "inc/LightSource.h"

LightSource::LightSource(){}
LightSource::LightSource(const GVector3& pos,const GVector3& ka,const GVector3& kd,const GVector3& ks):
  m_Position(pos),m_Ka(ka),m_Kd(kd),m_Ks(ks){}

void LightSource::setPosition(const GVector3& pos){
  m_Position=pos;
}
void LightSource::setKa(const GVector3& ka) {
  m_Ka=ka;
}
void LightSource::setKd(const GVector3& kd) {
  m_Kd=kd;
}
void LightSource::setKs(const GVector3& ks) {
  m_Ks=ks;
}
GVector3 LightSource::getPosition() const {
  return m_Position;
}
GVector3 LightSource::getKa() const {
  return m_Ka;
}
GVector3 LightSource::getKd() const {
  return m_Kd;
}
GVector3 LightSource::getKs() const {
  return m_Ks;
}
