#include "EngineCore/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace Delta
{

bool Window::sIsGLFWInitialized = false;

std::vector<GLfloat> vertices = {
	// position		     // color
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,	 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f,	 1.0f, 0.0f, 1.0f,
	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
};

std::vector<GLuint> indices = {
	0, 1, 2,
	2, 1, 3
};

const GLchar* vertexShaderCode =
	"#version 330 core\n"
	"layout (location = 0) in vec3 vPosition;\n"
	"layout (location = 1) in vec3 vColor;\n"
	"out vec3 fColor;\n"
	"void main() {\n"
	"	fColor = vColor;\n"
	"	gl_Position = vec4(vPosition, 1.0f);\n"
	"}\n";

const GLchar* fragmentShaderCode =
	"#version 330 core\n"
	"in vec3 fColor;\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(fColor, 1.0f);\n"
	"}\n";

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

	glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
	LOG_INFO("ImGui initialized succesfully");

	if (mShaderProgram.init(vertexShaderCode, fragmentShaderCode) == false)
		return -4;

	GlBufferLayout layout({ GlShaderData::Type::FLOAT3, GlShaderData::Type::FLOAT3 });

	mVBO.init(vertices, layout);
	mEBO.init(indices);

	mVAO.init();
	mVAO.addVertexBuffer(mVBO);
	mVAO.setIndexBuffer(mEBO);

	return 0;
}

void Window::shutdown()
{
	mVBO.clear();
	mVAO.clear();

	mShaderProgram.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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
		glClearColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		mShaderProgram.bind();
		mVAO.bind();
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, mVAO.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
		mVAO.unbind();
		mShaderProgram.unbind();

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

} // namespace Delta
