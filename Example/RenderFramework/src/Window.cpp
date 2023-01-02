#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

bool Window::sIsGLFWInitialized = false;

int Window::init(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
	mData.width = aWindowWidth;
	mData.height = aWindowHeight;
	mData.title = std::string(aTitle);


	if (!sIsGLFWInitialized && !glfwInit())
	{
		LOG_ERROR("Can't initialize GLFW!");
		return -1;
	}
	LOG_INFO("GLFW initialized succesfully");
	sIsGLFWInitialized = true;

	mWindow = glfwCreateWindow(aWindowWidth, aWindowHeight, aTitle, nullptr, nullptr);
	if (!mWindow)
	{
		LOG_ERROR("Can't create GLFW window");
		glfwTerminate();
		return -2;
	}
	LOG_INFO("GLFW window created succesfully");

	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Can't initialize OpenGL");
		return -3;
	}
	LOG_INFO("OpenGL initialized succesfully");

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
		MouseMoveEvent event(xpos, ypos);
		params->eventCallback(event);
	});

	glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
	{
		const auto params = static_cast<WindowParameters*>(glfwGetWindowUserPointer(window));
		WindowCloseEvent event;
		params->eventCallback(event);
	});


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui_ImplGlfw_InitForOpenGL(mWindow, true);

    return 0;
}

void Window::shutdown()
{
	if (sIsGLFWInitialized)
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}
	LOG_INFO("Window terminated");
}

void Window::onUpdate()
{
	if (sIsGLFWInitialized)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], 1.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();
		ImGui::Begin("Editor Window");
		ImGui::ColorEdit3("Background color", mBackgroundColor);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}
