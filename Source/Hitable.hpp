#pragma once
#include "Ray.hpp"
#include <glm/glm.hpp>

namespace RayTracer
{
    struct HitRecord
    {
        float T;
        glm::vec3 P;
        glm::vec3 Normal;
    };

    class IHitable
    {
    public:
        IHitable() = default;
        virtual ~IHitable() = default;
        virtual bool Hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
    };
}
