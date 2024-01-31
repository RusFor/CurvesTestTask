#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

#include "Curve.h"
#include "cmath"

class CURVELIBRARY_API Helix3D : public Curve {
public:
	Helix3D(double radius, double step)
	: radius_(std::abs(radius))
	, step_(step){};
	virtual Point3D GetPoint3D(double phi) const override;
	virtual Vector3D GetVector3D(double phi) const override;
	virtual bool IsCircle() const override;
	double GetRadius() const override;
private:
	double radius_;
	double step_;	
};

