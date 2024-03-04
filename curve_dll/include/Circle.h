#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

#include "Curve.h"

namespace curve {

class CURVELIBRARY_API Circle : public Curve {
public:
	Circle(double radius);

	virtual Point3D GetPoint3D(double phi) const override;

	virtual Vector3D GetVector3D(double phi) const override;

	virtual Type GetType() const override;

	double GetRadius() const;

private:
	double radius_;
};
}

