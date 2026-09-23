#pragma once

#include "Hittable.h"
#include "Material.h"

class Camera
{
public:
	double aspectRadio = 1.0;
	int imageWidth = 100;
	int samplesPerPixel = 10; // random samples for pixel
	int maxDepth = 10;


	void Render(const Hittable& world)
	{
		Initialize();

		std::cout << "P3\n" << imageWidth << ' ' << mImageHeight << "\n255\n";

		for (int scanlineIndex = 0; scanlineIndex < mImageHeight; scanlineIndex++)
		{
			std::clog
				<< "\rScanlines remaining: "
				<< (mImageHeight - scanlineIndex)
				<< ' '
				<< std::flush;

			for (int pixelIndex = 0; pixelIndex < imageWidth; pixelIndex++)
			{
				Color pixelColor(0.0, 0.0, 0.0);

				for (int sampleIndex = 0; sampleIndex < samplesPerPixel; sampleIndex++)
				{
					Ray ray = GetRay(pixelIndex, scanlineIndex);
					pixelColor += RayColor(ray,maxDepth , world);

				}

				WriteColor(std::cout, mPixelSamplesScale * pixelColor);
			}
		}

		std::clog << "\rDone.          \n";
	}


private :
	void Initialize()
	{
		mImageHeight = static_cast<int>(imageWidth / aspectRadio);
		mImageHeight = (mImageHeight < 1) ? 1 : mImageHeight;

		mPixelSamplesScale = 1.0 / static_cast<double>(samplesPerPixel);

		mCenter = Point3(0.0, 0.0, 0.0);

		//Viewpoert
		auto focalLength = 1.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / mImageHeight);

		//Vector view horizontal and down
		auto viewportU = Vec3(viewportWidth, 0.0, 0.0);
		auto viewportV = Vec3(0.0, -viewportHeight, 0.0);

		//delta vectors form pixel to pixel
		mPixelDeltaU = viewportU / imageWidth;
		mPixelDeltaV = viewportV / mImageHeight;

		auto viewportUpperLeft =
			mCenter
			- Vec3(0.0, 0.0, focalLength)
			- viewportU / 2.0
			-viewportV / 2.0;

			mPixel00Location = viewportUpperLeft + 0.5 * (mPixelDeltaU + mPixelDeltaV);

	}
	
	Ray GetRay(int pixelIndex, int scanlineIndex) const
	{

		auto offset = SampleSquare();

		auto pixelSample =
			mPixel00Location
			+ ((pixelIndex + offset.X()) * mPixelDeltaU)
			+ ((scanlineIndex + offset.Y()) * mPixelDeltaV);

		auto rayOrigin = mCenter;
		auto rayDirection = pixelSample - rayOrigin;

		return Ray(rayOrigin, rayDirection);
	}

	Vec3 SampleSquare() const
	{
		//return randomvalue -0.5 ~ 0.5
		return Vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0.0);
	}

	Color RayColor(const Ray& ray,int depth,const Hittable& world) const
	{
		HitRecord hitRecord;

		if (depth <= 0)
		{
			return Color(0.0, 0.0, 0.0);
		}



		if (world.Hit(ray, Interval(0.001, Infinity), hitRecord))
		{
			
			Ray scattered;
			Color attenuation;

			if (hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
			{
				return attenuation * RayColor(scattered, depth - 1, world);
			}

			return Color(0.0, 0.0, 0.0);
		}

		Vec3 unitDirection = UnitVector(ray.Direction());

		auto a = 0.5 * (unitDirection.Y() + 1.0);

		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);


	}

private:
	

	double mPixelSamplesScale = 1.0; //color scale factor sum of pixel samples;

	int mImageHeight = 0; //renedered image height;
	Point3 mCenter; 
	Point3 mPixel00Location; // 0,0
	Vec3 mPixelDeltaU;
	Vec3 mPixelDeltaV;
};