#include "DeltaEngine/Time.hpp"

#include <GLFW/glfw3.h>

namespace Delta
{

double Time::GetNativeTime()
{
    return glfwGetTime();
}

} // namespace Delta
