#include "DeltaEngine/Time.hpp"

#include <GLFW/glfw3.h>

namespace Delta
{

float Time::GetSeconds()
{
    return static_cast<float>(glfwGetTime());
}

} // namespace Delta
