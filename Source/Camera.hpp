#pragma once
#include "Ray.hpp"

namespace RayTracer
{
    class Camera
    {
    public:
        Camera()
        {
            mLowerLeftCorner = glm::vec3(-2.0f, -1.0f, -1.0f);
            mHorizontal = glm::vec3(4.0, 0.0, 0.0);
            mVertical = glm::vec3(0.0f, 2.0f, 0.0f);
            mOrigin = glm::vec3(0.0f);
        }
        Ray GetRay(float u, float v)
        {
            return Ray(mOrigin, mLowerLeftCorner + u * mHorizontal + v * mVertical - mOrigin);
        }
    private:
        glm::vec3 mLowerLeftCorner;
        glm::vec3 mHorizontal;
        glm::vec3 mVertical;
        glm::vec3 mOrigin;
    };
}