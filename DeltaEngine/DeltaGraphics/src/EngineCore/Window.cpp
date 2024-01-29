#include "PCH.hpp"
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

int Window::Init(unsigned int windowWidth, unsigned int windowHeight, const char* title)
{
    LOG_INFO("Creating window {0} ({1}, {2})", title, windowWidth, windowHeight);
    m_Data.width = windowWidth;
    m_Data.height = windowHeight;
    m_Data.title = std::string(title);

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
    m_Window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
    if (!m_Window)
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

    if (!Renderer::Init(m_Window))
        return -3;

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        params->width = width;
        params->height = height;

        WindowResizeEvent event(width, height);
        params->eventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        MouseMoveEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
        params->eventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
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

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        params->eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        params->eventCallback(event);
    });

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        Renderer::Viewport(width, height);
    });

    Renderer::Viewport(m_Data.width, m_Data.height);

    Gui::OnWindowCreate(m_Window);

    return 0;
}

void Window::Shutdown()
{
    Gui::OnWindowClose();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

    LOG_INFO("Window terminated");
}

void Window::OnUpdate()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

} // namespace Delta
