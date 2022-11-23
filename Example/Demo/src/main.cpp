#include <iostream>
#include <memory>
#include <Application.hpp>

class DemoApplication : public Application
{
    void onUpdate() override
    {
        std::cout << "Hello Demo!" << std::endl;
    }
};

int main()
{
    const auto app = std::make_unique<DemoApplication>();
    return app->start(1024, 768, "Demo");
}
