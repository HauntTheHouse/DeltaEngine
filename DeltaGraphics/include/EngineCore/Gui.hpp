#pragma once

struct GLFWwindow;

namespace Delta
{

class Gui
{
public:
    static void onWindowCreate(GLFWwindow* aWindow);
    static void onWindowClose();
    static void onDrawBegin();
    static void onDrawEnd();

};

} // namespace Delta