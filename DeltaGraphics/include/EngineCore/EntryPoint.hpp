#pragma once

#include "Application.hpp"

extern Delta::Application* Delta::createApplication();

int main(int argc, char** argv)
{
    auto app = Delta::createApplication();
    app->run();
    delete app;
    return 0;
}
