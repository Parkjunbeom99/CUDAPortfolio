#pragma once

#include"Shared.h"
#include "Ray.h"

class HitRecord
{
public:

	void SetFaceNormal(const Ray& r, const Vec3& outwardNormal)
	{
		bFrontFace = Dot(r.Direction(), outwardNormal) < 0;
		Normal = bFrontFace ? outwardNormal : -outwardNormal;
	}

	Point3 P;
	Vec3 Normal;
	double T;
	bool bFrontFace;
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const Ray& r, const Interval& ray, HitRecord& rec)const = 0;

};