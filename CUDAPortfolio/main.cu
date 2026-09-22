#include"Color.h"
#include "Vector3.h"
#include "Ray.h"



#include<iostream>
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

double HitSphere(const Point3& center, double radius, const Ray& r)
{
	Vec3 oc = center - r.Origin();
	auto a = r.Direction().LengthSquared();
	auto h = Dot(r.Direction(), oc);
	auto c = oc.LengthSquared() - radius * radius;

	auto discriminant = h * h - a * c;


	if (discriminant < 0.0)
	{
		return -1.0;

	}

	return (h - std::sqrt(discriminant)) / a;

	
}

Color RayColor(const Ray& r, const Hittable& world)
{
	HitRecord hitRecord;

	if (world.Hit(r, Interval(0.0, Infinity), hitRecord))
	{
		return 0.5 * (hitRecord.Normal + Color(1.0, 1.0, 1.0));
	}


	Vec3 unitDirection = UnitVector(r.Direction());
	auto a = 0.5 * (unitDirection.Y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
	// 16:9
	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;

	int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	//world
	HittableList world;
	world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
	world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));


	//camera

	auto focalLength = 1.0f;
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
	auto cameraCenter = Point3(0, 0, 0);


	//calculate vector  viewport uv
	auto viewportU = Vec3(viewportWidth, 0, 0);
	auto viewportV = Vec3(0, -viewportHeight, 0);

	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
	auto pixel100Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	//render
	
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; j++)
	{
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; i++)
		{
			auto pixelCenter = pixel100Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			Ray r(cameraCenter, rayDirection);

			Color pixelColor = RayColor(r, world);
			WriteColor(std::cout, pixelColor);
		}
	}
	
	std::clog << "\rDone.                \n";
	return 0;
}