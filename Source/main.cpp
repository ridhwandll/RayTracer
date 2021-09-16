#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stb_image_write.h>
#include <windows.h>
#include <shellapi.h>
#define NUM_CHANNELS 3

#include "Ray.hpp"
#include "Hitable.hpp"
#include "Sphere.hpp"
#include "HitableList.hpp"
#include "Camera.hpp"
#include "Random.hpp"

#ifndef _WIN32
    #error This ray tracer is Windows only!
#endif
using namespace RayTracer;

glm::vec3 RandomPointInUintSphere()
{
    glm::vec3 p;
    do
    {
        p = 2.0f * glm::vec3(Random::Generate<float>(0, 1), Random::Generate<float>(0, 1), Random::Generate<float>(0, 1)) - glm::vec3(1.0f);
    } while ((p.x * p.x + p.y * p.y + p.z * p.z) >= 1.0f);
    return p;
}

glm::vec3 Color(const Ray& ray, IHitable* world)
{
    HitRecord rec;
    if (world->Hit(ray, 0.001, FLT_MAX, rec))
    {
        glm::vec3 target = rec.P + rec.Normal + RandomPointInUintSphere();
        return 0.5f * Color(Ray(rec.P, target - rec.P), world);
    }
    else
    {
        glm::vec3 unitDirection = glm::normalize(ray.Direction()); //Made it a unit vector so -1.0 < y < 1.0
        float t = 0.5 * (unitDirection.y + 1.0); //0.0 < t < 1.0
        return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f); //Blended Value = (1-t) * startValue + t * endValue
    }
}

int main()
{
    int width  = 2000;
    int height = 1000;
    int numSamples = 10;
    bool antialiasing = true;

    uint32_t size = width * height * NUM_CHANNELS;
    char* pixels = new char[size];
    uint32_t index = 0;

    IHitable* list[2];
    list[0] = new Sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new Sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100);

    IHitable* world = new HitableList(list, 2);
    Camera cam;

    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

            if (antialiasing)
            {
                for (int s = 0; s < numSamples; s++)
                {
                    float u = float(i + Random::Generate<float>(0, 1)) / float(width);
                    float v = float(j + Random::Generate<float>(0, 1)) / float(height);
                    Ray r = cam.GetRay(u, v);
                    color += Color(r, world);
                }
                color /= float(numSamples);
                color = glm::vec3(glm::sqrt(color.r), glm::sqrt(color.g), glm::sqrt(color.b));
            }
            else
            {
                float u = float(i) / float(width);
                float v = float(j) / float(height);
                Ray r = cam.GetRay(u, v);
                color += Color(r, world);
            }

            int ir = int(255.99 * color.r);
            int ig = int(255.99 * color.g);
            int ib = int(255.99 * color.b);

            pixels[index++] = ir;
            pixels[index++] = ig;
            pixels[index++] = ib;
        }
        printf("Progress: %i/%i\n", index, size);
    }

    const std::string outputImagePath = std::filesystem::absolute(std::filesystem::path("Output/HelloWorld.png")).string();

    if (stbi_write_png(outputImagePath.c_str(), width, height, NUM_CHANNELS, pixels, width * NUM_CHANNELS))
        ShellExecute(NULL, "open", (outputImagePath).c_str(), NULL, NULL, SW_SHOWNORMAL);

    delete[] pixels;
}
