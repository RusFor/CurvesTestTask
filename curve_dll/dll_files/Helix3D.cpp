#include "pch.h"
#include "Helix3d.h"

#include <numbers>
#include <cmath>
#include <stdexcept>

using std::numbers::pi;
namespace curve {

Helix3D::Helix3D(double radius, double step)
	: radius_(radius)
	, step_(step) {
	if(radius < 0.) {
		throw std::invalid_argument("Radius must be non-negative.");
	}
}

Point3D Helix3D::GetPoint3D(double phi) const {
	double x = radius_ * std::cos(phi);
	double y = radius_ * std::sin(phi);
	double z = (step_ * phi) / (2 * pi);

	return {x,y,z};
}

Vector3D Helix3D::GetVector3D(double phi) const {
	double x = -radius_ * std::sin(phi);
	double y = radius_ * std::cos(phi);
	double z = step_ / (2 * pi);

	return {x,y,z};
}

Type Helix3D::GetType() const {
	return Type::Helix3D;
}

}