#include"Color.h"
#include "Vector3.h"

#include<iostream>

int main()
{
	//이미지
	int ImageWidth = 256;
	int ImageHeight = 256;

	//렌더
	std::cout << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";


	for (int j = 0; j < ImageHeight; j++)
	{
		std::clog << "\rScanlines remaining " << (ImageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < ImageWidth; i++)
		{
			
			auto pixelColor = Color(double(i) / (ImageHeight - 1), double(j) / (ImageHeight - 1), 0);
			WriteColor(std::cout, pixelColor);


		}
	}
	std::clog << "\rDone.            \n";
	
	return 0;
}