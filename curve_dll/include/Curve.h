#pragma once

#ifdef CURVELIBRARY_EXPORTS
#define CURVELIBRARY_API __declspec(dllexport)
#else
#define CURVELIBRARY_API __declspec(dllimport)
#endif

struct CURVELIBRARY_API Point3D {
	Point3D(double ax, double ay, double az)
		: x(ax)
		, y(ay)
		, z(az) {}
	double x;
	double y;
	double z;
};

struct CURVELIBRARY_API Vector3D {
	Vector3D(double ax, double ay, double az)
		: x(ax)
		, y(ay)
		, z(az) {}
	double x;
	double y;
	double z;
};

class CURVELIBRARY_API Curve {
public:
	virtual Point3D GetPoint3D(double phi) const = 0;
	virtual Vector3D GetVector3D(double phi) const = 0;
	virtual bool IsCircle() const = 0;
	virtual double GetRadius() const = 0;
	virtual ~Curve() {};
};

