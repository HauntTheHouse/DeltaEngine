#include "EngineCore/Application.hpp"

class DemoApplication : public Delta::Application
{
    void onUpdate() override
    {
    }
};

int main()
{
    const auto app = std::make_unique<DemoApplication>();
    return app->start(1024, 768, "Demo");
}
