#pragma once

#include"Shared.h"
#include "Ray.h"


class Material;

class HitRecord
{
public:

	void SetFaceNormal(const Ray& r, const Vec3& outwardNormal)
	{
		isFrontFace = Dot(r.Direction(), outwardNormal) < 0;
		normal = isFrontFace ? outwardNormal : -outwardNormal;
	}

	Point3 point;
	Vec3 normal;
	double T;
	bool isFrontFace =false;
	std::shared_ptr<Material> material;
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool Hit(const Ray& r, const Interval& ray, HitRecord& rec)const = 0;

};