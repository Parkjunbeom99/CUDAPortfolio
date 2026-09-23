#pragma once

#include"Hittable.h"
#include "Shared.h"

#include<cmath>
#include<iostream>
#include<memory>


class Sphere : public Hittable
{
public :
	Sphere(const Point3& center, double radius, const std::shared_ptr<Material>& material)
		:mCenter(center),mRadius(std::fmax(0.0, radius)),mMaterial(material)
	{

	}

	virtual bool Hit(const Ray& r, const Interval& rayT, HitRecord& rec) const override
	{
		Vec3 originToCenter = mCenter - r.Origin();

		auto a = r.Direction().LengthSquared();
		auto h = Dot(r.Direction(), originToCenter);
		auto c = originToCenter.LengthSquared() - mRadius * mRadius;

		auto discriminant = h * h - a * c;

		if (discriminant < 0.0)
		{
			return false;
		}

		auto squaredRootDiscriminant = std::sqrt(discriminant);

		auto root = (h - squaredRootDiscriminant) / a;

		if (!rayT.Surrounds(root))
		{
			root = (h + squaredRootDiscriminant) / a;
			if (!rayT.Surrounds(root))
			{
				return false; 
			}
		}
		rec.T = root;
		rec.point = r.At(rec.T);

		Vec3 outwardNormal = (rec.point - mCenter) / mRadius;
		rec.SetFaceNormal(r, outwardNormal);

		rec.material = mMaterial;

		return true;
	}

private :
	Point3 mCenter;
	double mRadius;
	std::shared_ptr<Material> mMaterial;


};