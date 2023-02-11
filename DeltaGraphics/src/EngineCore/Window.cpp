#include "EngineCore/Window.hpp"

#ifdef USING_VULKAN
#include <vulkan/vulkan.h>
#endif
#include <GLFW/glfw3.h>

#include "EngineCore/Event.hpp"
#include "EngineCore/Rendering/Renderer.hpp"
#include "EngineCore/Gui.hpp"

namespace Delta
{

int Window::init(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
    LOG_INFO("Creating window {0} ({1}, {2})", aTitle, aWindowWidth, aWindowHeight);
    mData.width = aWindowWidth;
    mData.height = aWindowHeight;
    mData.title = std::string(aTitle);

    glfwSetErrorCallback([](int errorCode, const char* description)
    {
        LOG_ERROR("GLFW error {0}: {1}", errorCode, description);
    });

    if (!glfwInit())
    {
        LOG_ERROR("GLFW initialization failed");
        return -1;
    }
    LOG_INFO("GLFW initialized succesfully");

#ifdef USING_VULKAN
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
    mWindow = glfwCreateWindow(aWindowWidth, aWindowHeight, aTitle, nullptr, nullptr);
    if (!mWindow)
    {
        LOG_ERROR("GLFW window creation failed");
        glfwTerminate();
        return -2;
    }
    LOG_INFO("GLFW window created succesfully");

#ifdef USING_VULKAN
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::cout << extensionCount << " extensions supported\n";
#endif

    if (!Renderer::init(mWindow))
        return -3;

    glfwSetWindowUserPointer(mWindow, &mData);

    glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        params->width = width;
        params->height = height;

        WindowResizeEvent event(width, height);
        params->eventCallback(event);
    });

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        MouseMoveEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
        params->eventCallback(event);
    });

    glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(static_cast<KeyCode>(key), false);
                params->eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(static_cast<KeyCode>(key), true);
                params->eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(static_cast<KeyCode>(key));
                params->eventCallback(event);
                break;
            }
            default:
                break;
        }
    });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        switch (action)
        {
        case GLFW_PRESS:
        {
            MouseButtonPressedEvent event(static_cast<MouseButtonCode>(button), static_cast<float>(xpos), static_cast<float>(ypos));
            params->eventCallback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            MouseButtonReleasedEvent event(static_cast<MouseButtonCode>(button), static_cast<float>(xpos), static_cast<float>(ypos));
            params->eventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        params->eventCallback(event);
    });

    glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        params->eventCallback(event);
    });

    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
    {
        Renderer::viewport(width, height);
    });

    Renderer::viewport(mData.width, mData.height);

    Gui::onWindowCreate(mWindow);

    return 0;
}

void Window::shutdown()
{
    Gui::onWindowClose();

    glfwDestroyWindow(mWindow);
    glfwTerminate();

    LOG_INFO("Window terminated");
}

void Window::onUpdate()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

} // namespace Delta
