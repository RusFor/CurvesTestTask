#include "pch.h"
#include "Circle.h"
#include "cmath"

Point3D  Circle::GetPoint3D(double phi) const {
	double x = radius_ * std::cos(phi);
	double y = radius_ * std::sin(phi);
	double z = 0;

	return {x,y,z};
}

Vector3D Circle::GetVector3D(double phi) const {
	double x = -radius_ * std::sin(phi);
	double y = radius_ * std::cos(phi);
	double z = 0;

	return {x,y,z};
}

bool Circle::IsCircle() const {
	return true;
}

double Circle::GetRadius() const {
	return radius_;
}
