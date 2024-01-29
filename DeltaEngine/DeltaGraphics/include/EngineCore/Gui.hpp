#pragma once

struct GLFWwindow;

namespace Delta
{

class Gui
{
public:
    static void OnWindowCreate(GLFWwindow* window);
    static void OnWindowClose();
    static void OnDrawBegin();
    static void OnDrawEnd();

};

} // namespace Delta
