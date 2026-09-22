#pragma once

#include <iostream>
#include"Shared.h"

using Color = Vec3;

void WriteColor(std::ostream& out, const Color& pixelColor)
{
	auto r = pixelColor.X();
	auto g = pixelColor.Y();
	auto b = pixelColor.Z();


	//resize
	int rByte = int(255.999 * r);
	int gByte = int(255.999 * g);
	int bByte = int(255.999 * b);

	out << rByte << ' ' << gByte << ' ' << bByte << '\n';

}