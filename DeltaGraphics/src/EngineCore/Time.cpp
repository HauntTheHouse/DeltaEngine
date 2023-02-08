#include "EngineCore/Time.hpp"

#include <GLFW/glfw3.h>

namespace Delta
{

float Time::get()
{
    return static_cast<float>(glfwGetTime());
}

}
