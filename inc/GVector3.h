#ifndef GVECTOR3_H

#define GVECTOR3_H
#include <iostream>

class GVector3 {
  public:  
    double x;
    double y;
    double z;
  public:
    friend std::ostream& operator<<(std::ostream&,const GVector3&);
    friend std::istream& operator>>(std::istream&,GVector3&);
    GVector3();
    GVector3(const GVector3&);
    GVector3(double,double,double);
    double length() const;
    //false if the length==0
    bool normalize();
    GVector3 cross(const GVector3&);
    GVector3 operator=(const GVector3&);
    GVector3 operator=(double);
    GVector3 operator+(const GVector3&) const;
    GVector3 operator+=(const GVector3&);
    GVector3 operator-(const GVector3&) const;
    GVector3 operator-=(const GVector3&);
    GVector3 operator*(const double) const;
    GVector3 operator*=(const double);
    double operator*(const GVector3&) const;
    GVector3 operator/(const double) const;
    GVector3 operator/=(const double);
};
std::ostream& operator<<(std::ostream&,const GVector3&);
std::istream& operator>>(std::istream&,GVector3&);

#endif /* end of include guard: GVECTOR3_H */
