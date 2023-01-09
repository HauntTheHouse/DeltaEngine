#pragma once

struct GLFWwindow;

namespace Delta
{

class GUIModule
{
public:
    static void onWindowCreate(GLFWwindow* aWindow);
    static void onWindowClose();
    static void onDrawBegin();
    static void onDrawEnd();

    static void ShowExampleAppDockSpace();

};

} // namespace Delta
