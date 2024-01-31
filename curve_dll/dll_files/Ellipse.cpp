#include "pch.h"
#include "Ellipse.h"
#include "cmath"

Point3D Ellipse::GetPoint3D(double phi) const {
	double x = radius_x_ * std::cos(phi);
	double y = radius_y_ * std::sin(phi);
	double z = 0;
	
	return {x,y,z};
}

Vector3D Ellipse::GetVector3D(double phi) const {
	double x = - radius_x_ * std::sin(phi);
	double y = radius_y_ * std::cos(phi);
	double z = 0;

	return {x,y,z};
}

bool Ellipse::IsCircle() const {
	return radius_x_ == radius_y_;
}

double Ellipse::GetRadius() const {
	return radius_x_;
}
