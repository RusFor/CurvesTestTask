#include "pch.h"
#include "Helix3d.h"

#include "numbers"
#include "cmath"

using std::numbers::pi;

Point3D Helix3D::GetPoint3D(double phi) const {
	double x = radius_ * std::cos(phi);
	double y = radius_ * std::sin(phi);
	double z = (step_ * phi) / (2*pi);

	return {x,y,z};
}

Vector3D Helix3D::GetVector3D(double phi) const {
	double x = - radius_ * std::sin(phi);
	double y = radius_ * std::cos(phi);
	double z = step_ / (2 * pi);

	return {x,y,z};
}

bool Helix3D::IsCircle() const {
	return step_ == 0;
}

double Helix3D::GetRadius() const {
	return radius_;
}
