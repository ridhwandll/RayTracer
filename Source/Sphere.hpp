#pragma once
#include "Hitable.hpp"

namespace RayTracer
{
    class Sphere : public IHitable
    {
    public:
        Sphere() = default;
        Sphere(const glm::vec3& centre, float radius)
            : mCentre(centre), mRadius(radius) {}

        virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override
        {
            glm::vec3 oc = r.Origin() - mCentre;
            float a = glm::dot(r.Direction(), r.Direction());
            float b = glm::dot(oc, r.Direction());
            float c = glm::dot(oc, oc) - mRadius * mRadius;
            float discriminant = b * b - a * c;
            if (discriminant > 0.0f)
            {
                float temp = (-b - sqrt(b * b - a * c)) / a;
                if (temp < tMax && temp > tMin)
                {
                    rec.T = temp;
                    rec.P = r.PointAtParameter(rec.T);
                    rec.Normal = (rec.P - mCentre) / mRadius;
                    return true;
                }

                temp = (-b + sqrt(b * b - a * c)) / a;
                if (temp < tMax && temp > tMin)
                {
                    rec.T = temp;
                    rec.P = r.PointAtParameter(rec.T);
                    rec.Normal = (rec.P - mCentre) / mRadius;
                    return true;
                }
            }
            return false;
        }
    private:
        glm::vec3 mCentre;
        float mRadius;
    };
}
