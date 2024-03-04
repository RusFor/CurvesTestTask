#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

#include "Curve.h"

namespace curve {

class CURVELIBRARY_API Ellipse : public Curve {
public:

	Ellipse(double radius_x, double radius_y);

	Point3D GetPoint3D(double phi) const override;

	Vector3D GetVector3D(double phi) const override;

	Type GetType() const override;

private:
	double radius_x_;
	double radius_y_;
};
}

