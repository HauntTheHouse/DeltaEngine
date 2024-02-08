#pragma once

#include "Application.hpp"

extern Delta::Application* Delta::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Delta::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
