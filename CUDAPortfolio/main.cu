#include"Color.h"
#include "Vector3.h"
#include "Ray.h"

#include<iostream>
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Metal.h"

int main()
{


	HittableList world;

	//auto R = std::cos(Pi / 4);

	//auto materialleft = std::make_shared<Lambertian>(Color(0,0,1));
	//auto materialright = std::make_shared <Lambertian> (Color(1,0, 0));

	//world.Add(std::make_shared<Sphere>(Point3(-R, 0.0, -1.0), R, materialleft));
	//world.Add(std::make_shared<Sphere>(Point3(R ,0.0, -1.0), R, materialright));
	
	auto materialground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto materialcenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto materialleft = std::make_shared<Dielectric>(1.50);
	auto materialbubble = std::make_shared<Dielectric>(1.0 / 1.50);
	auto materialright = std::make_shared <Metal> (Color(0.8, 0.6, 0.2), 1.0);

	world.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialground));
	world.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, materialcenter));
	world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialleft));
	world.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, materialbubble));
	world.Add(std::make_shared<Sphere>(Point3(1.0 ,0.0, -1.0), 0.5, materialright));



	Camera camera;

	camera.aspectRadio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;
	camera.maxDepth = 50;

	camera.vfov = 90;
	camera.lookfrom = Point3(-2, 2, 1);
	camera.lookat = Point3(0, 0, -1);
	camera.vup = Vec3(0, 1, 0);


	camera.defocus_angle = 10.0;
	camera.focus_dist = 3.4;


	camera.Render(world);

}