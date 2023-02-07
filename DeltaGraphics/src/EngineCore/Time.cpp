#include "EngineCore/Time.hpp"

#include <GLFW/glfw3.h>

namespace Delta
{

double Time::get()
{
    return glfwGetTime();
}

}
