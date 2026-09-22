#pragma once

#include "Hittable.h"
#include"Shared.h"
#include<memory>
#include<vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
public:
	HittableList() = default;

	explicit HittableList(const std::shared_ptr <Hittable>& object)
	{
		Add(object);
	}

	void Add(const std::shared_ptr<Hittable>& object)
	{
		mObjects.push_back(object);
	}

	void Clear()
	{
		mObjects.clear();

	}

	virtual bool Hit(const Ray& r, const Interval& rayT, HitRecord& rec)const override
	{
		HitRecord temporaryHitRecord;
		bool bHitAnyThing = false;
		auto closestSoFar = rayT.Max;

		for (const auto& object : mObjects)
		{
			Interval currentRayT(rayT.Min, closestSoFar);
			if (object->Hit(r, currentRayT, temporaryHitRecord))
			{
				bHitAnyThing = true;
				closestSoFar = temporaryHitRecord.T;
				rec = temporaryHitRecord;
			}
		}
		return bHitAnyThing;
	}
private:
	std::vector<std::shared_ptr<Hittable>>mObjects;

};