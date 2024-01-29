#include "PCH.hpp"
#include "EngineCore/Time.hpp"

#include <GLFW/glfw3.h>

namespace Delta
{

float Time::Get()
{
    return static_cast<float>(glfwGetTime());
}

} // namespace Delta
