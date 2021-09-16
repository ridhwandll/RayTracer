#pragma once
#include "Hitable.hpp"

namespace RayTracer
{
    class HitableList : public IHitable
    {
    public:
        HitableList() = default;
        HitableList(IHitable** l, int n) { mList = l; mSize = n; }
        virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override
        {
            HitRecord tempRecord;
            bool hitAnything = false;
            double closestSoFar = tMax;
            for (int i = 0; i < mSize; i++)
            {
                if (mList[i]->Hit(r, tMin, closestSoFar, tempRecord))
                {
                    hitAnything = true;
                    closestSoFar = tempRecord.T;
                    rec = tempRecord;
                }
            }
            return hitAnything;
        }
    private:
        IHitable** mList;
        int mSize;
    };
}
