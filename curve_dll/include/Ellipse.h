#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

#include "Curve.h"
#include "cmath"

class CURVELIBRARY_API Ellipse : public Curve {
public:
	Ellipse(double radius_x,double radius_y) 
		: radius_x_(std::abs(radius_x)) 
		, radius_y_(std::abs(radius_y)){}
	Point3D GetPoint3D(double phi) const override;
	Vector3D GetVector3D(double phi) const override;
	bool IsCircle() const override;
	double GetRadius() const override;
private:
	double radius_x_;
	double radius_y_;
	
};

