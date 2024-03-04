#include "pch.h"
#include "Circle.h"

#include <cmath>
#include <stdexcept>

namespace curve {
Circle::Circle(double radius)
	: radius_(radius) {
	if(radius < 0.) {
		throw std::invalid_argument("Radius must be non-negative.");
	}
}
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

Type Circle::GetType() const {
	return Type::Circle;
}

double Circle::GetRadius() const {
	return radius_;
}
}
