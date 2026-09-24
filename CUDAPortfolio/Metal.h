#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Color& albedo, double fuzz)
		:mAlbedo(albedo) , mFuzz(fuzz< 1 ? fuzz :1)
	{


	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered)const override
	{
		Vec3 reflected = Reflect(rayIn.Direction(), hitRecord.normal);
		
		reflected = UnitVector(reflected) + (mFuzz * RandomUnitVector());

		scattered = Ray(hitRecord.point, reflected);

		attenuation = mAlbedo;

		return (Dot(scattered.Direction(), hitRecord.normal) > 0.0);
	}

private:
	Color mAlbedo;
	double mFuzz;
};

class Dielectric : public Material
{

public:
	Dielectric(double refractionIndex)
		:mRefractionIndex(refractionIndex)
	{

	}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& scattered)const override
	{
		attenuation = Color(1.0, 1.0, 1.0);

		const double refractionRatio =
			hitRecord.isFrontFace ? (1.0 / mRefractionIndex) : mRefractionIndex;

		const Vec3 unitDirection = UnitVector(rayIn.Direction());

		const double cosTheta =
			std::fmin(Dot(-unitDirection, hitRecord.normal), 1.0);

		const double sinTheta =
			std::sqrt(1.0 - cosTheta * cosTheta);

		const bool cannotRefract =
			refractionRatio * sinTheta > 1.0;

		Vec3 direction;

		if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble())
		{
			direction = Reflect(unitDirection, hitRecord.normal);

		}
		else
		{
			direction = Refract(unitDirection, hitRecord.normal, refractionRatio);
		}
		scattered = Ray(hitRecord.point, direction);



		return true;

	}

private:
	
	double mRefractionIndex = 1.0;

	static double Reflectance(double cosine, double refractionIndex)
	{

		auto r0 = (1.0 - refractionIndex) / (1.0 + refractionIndex);
		r0 = r0 * r0;
		return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5);

	}
};