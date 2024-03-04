#include "pch.h"
#include "Ellipse.h"

#include <cmath>
#include <stdexcept>

namespace curve {

Ellipse::Ellipse(double radius_x, double radius_y)
	: radius_x_(radius_x)
	, radius_y_(radius_y) {
	if(radius_x < 0. || radius_y < 0.) {
		throw std::invalid_argument("Radiuses must be non-negative.");
	}
}

Point3D Ellipse::GetPoint3D(double phi) const {
	double x = radius_x_ * std::cos(phi);
	double y = radius_y_ * std::sin(phi);
	double z = 0;

	return {x,y,z};
}

Vector3D Ellipse::GetVector3D(double phi) const {
	double x = -radius_x_ * std::sin(phi);
	double y = radius_y_ * std::cos(phi);
	double z = 0;

	return {x,y,z};
}

Type Ellipse::GetType() const {
	return Type::Ellipse;
}

}
