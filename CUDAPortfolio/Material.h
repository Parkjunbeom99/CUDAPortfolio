#pragma once

#include "Hittable.h"

class Material
{
public :
	virtual ~Material() = default;

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered)const
	{

		return false;
	}


};

class Lambertian : public Material
{
public:
	explicit Lambertian(const Color& albedo)
		:mAlbedo(albedo)
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered)const override
	{
		Vec3 scatterDirection = hitRecord.normal + RandomUnitVector();


		if (scatterDirection.NearZero())
		{
			scatterDirection = hitRecord.normal;
		}

		scattered = Ray(hitRecord.point, scatterDirection);
		attenuation = mAlbedo;

		return true;
	}

private:
	Color mAlbedo;
};

