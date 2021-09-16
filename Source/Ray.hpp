#pragma once
#include <glm/glm.hpp>

namespace RayTracer
{
    class Ray
    {
    public:
        Ray() = default;
        Ray(const glm::vec3& a, const glm::vec3& b) { mA = a; mB = b; }
        glm::vec3 Origin() const { return mA; }
        glm::vec3 Direction() const { return mB; }
        glm::vec3 PointAtParameter(float t) const { return mA + t * mB; }
    public:
        glm::vec3 mA;
        glm::vec3 mB;
    };
}
