#pragma once
#include <random>

namespace RayTracer
{
    class Random
    {
    public:
        template<typename T>
        static T Generate(T min, T max)
        {
            if constexpr (std::is_same_v<T, int>)
            {
                if (min > max)
                    std::swap(min, max);

                std::uniform_int_distribution<> distribution(min, max);
                auto& mt = Engine();
                return distribution(mt);
            }

            if constexpr (std::is_same_v<T, float>)
            {
                if (min > max)
                    std::swap(min, max);

                std::uniform_real_distribution<T> distribution(min, max);
                auto& mt = Engine();
                return distribution(mt);
            }

            if constexpr (std::is_same_v<T, double>)
            {
                if (min > max)
                    std::swap(min, max);

                std::uniform_real_distribution<T> distribution(min, max);
                auto& mt = Engine();
                return distribution(mt);
            }

            if constexpr (std::is_same_v<T, bool>)
            {
                std::bernoulli_distribution distribution(0.5);
                auto& mt = Engine();
                return distribution(mt);
            }

            if constexpr (!std::is_same_v<T, bool> || !std::is_same_v<T, int> || !std::is_same_v<T, float> || !std::is_same_v<T, double>)
            {
                assert(false, "Given data type in SPKRandom is not supported!");
                return -1;
            }
        }
    private:
        static std::mt19937_64& Random::Engine()
        {
            static std::random_device rd;
            static std::mt19937_64 engine(rd());
            return engine;
        }
    };
}
