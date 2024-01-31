#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

#include "Curve.h"
#include "cmath"

class CURVELIBRARY_API Circle : public Curve {
public:
	Circle(double radius)
		: radius_(std::abs(radius)) {};
	virtual Point3D GetPoint3D(double phi) const override;
	virtual Vector3D GetVector3D(double phi) const override;
	virtual bool IsCircle() const override;
	double GetRadius() const override;
private:
	double radius_;
};

