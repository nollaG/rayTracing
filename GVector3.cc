#include "inc/GVector3.h"
#include <cmath>
#include <iostream>

GVector3::GVector3():x(0.0f),y(0.0f),z(0.0f){}

GVector3::GVector3(const GVector3& rhs):x(rhs.x),y(rhs.y),z(rhs.z){}

GVector3::GVector3(double xx,double yy,double zz):x(xx),y(yy),z(zz){}

double GVector3::length() const {
  return sqrt(x*x+y*y+z*z);
}



bool GVector3::normalize() {
  double len=this->length();
  if (len==0)
    return false;
  x/=len;
  y/=len;
  z/=len;
  return true;
}

GVector3 GVector3::cross(const GVector3& rhs) {
  GVector3 result;
  result.x=y*rhs.z-z*rhs.y;
  result.y=z*rhs.x-x*rhs.z;
  result.z=x*rhs.y-y*rhs.x;
  return result;
}
GVector3 GVector3::operator=(const GVector3& rhs) {
  x=rhs.x;
  y=rhs.y;
  z=rhs.z;
  return *this;
}

GVector3 GVector3::operator=(double f) {
  x=f;
  y=f;
  z=f;
  return *this;
}

GVector3 GVector3::operator+(const GVector3& rhs) const {
  GVector3 g1(x+rhs.x,y+rhs.y,z+rhs.z);
  return g1;
}
GVector3 GVector3::operator+=(const GVector3& rhs) {
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  return *this;
}
GVector3 GVector3::operator-(const GVector3& rhs) const {
  GVector3 g1(x-rhs.x,y-rhs.y,z-rhs.z);
  return g1;
}
GVector3 GVector3::operator-=(const GVector3& rhs) {
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  return *this;
}

GVector3 GVector3::operator*(const double f) const {
  GVector3 g1(x*f,y*f,z*f);
  return g1;
}
GVector3 GVector3::operator*=(const double f) {
  x*=f;
  y*=f;
  z*=f;
  return *this;
}

double GVector3::operator*(const GVector3& rhs) const {
  return x*rhs.x+y*rhs.y+z*rhs.z;
}


GVector3 GVector3::operator/(const double f) const {
  GVector3 g1;
  if (f==0.0f)
    return g1;
  g1.x=x/f;
  g1.y=y/f;
  g1.z=z/y;
  return g1;
}
GVector3 GVector3::operator/=(const double f) {
  if (f==0.0f)
    return *this;
  x/=f;
  y/=f;
  z/=f;
  return *this;
}

bool GVector3::operator<(const GVector3& rhs) const {
  return length() < rhs.length();
}

bool GVector3::operator==(const GVector3& rhs) const {
  if (fabs(rhs.x-x)>EPILSON_FOR_COMPARE)
    return false;

  if (fabs(rhs.y-y)>EPILSON_FOR_COMPARE)
    return false;
  if (fabs(rhs.z-z)>EPILSON_FOR_COMPARE)
    return false;
  return true;
}

std::ostream& operator<<(std::ostream& os,const GVector3& g) {
  os << g.x << " " << g.y << " " << " " <<g.z;
  return os;
}
std::istream& operator>>(std::istream& is,GVector3& g) {
  is >> g.x >> g.y >> g.z;
  return is;
}

