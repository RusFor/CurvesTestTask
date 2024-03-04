#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

#include "Curve.h"

namespace curve {

class CURVELIBRARY_API Helix3D : public Curve {
public:
	Helix3D(double radius, double step);

	virtual Point3D GetPoint3D(double phi) const override;

	virtual Vector3D GetVector3D(double phi) const override;

	virtual Type GetType() const override;

private:
	double radius_;
	double step_;
};
}

