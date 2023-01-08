#include "EngineCore/Window.hpp"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include "EngineCore/Rendering/OpenGL/Renderer.hpp"
#include "EngineCore/Modules/GUIModule.hpp"

namespace Delta
{

std::vector<GLfloat> vertices = {
	// position		     // color
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,	  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,	  1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
};

std::vector<GLuint> indices = {
	0, 1, 2,
	2, 1, 3
};

const char* vertexShaderCode =
    R"(#version 330 core
       layout (location = 0) in vec3 vPosition;
       layout (location = 1) in vec3 vColor;
       uniform mat4 uModel;
	   uniform mat4 uViewProject;
       out vec3 fColor;
       void main() {
           fColor = vColor;
           gl_Position = uViewProject * uModel * vec4(vPosition, 1.0f);
       })";

const char* fragmentShaderCode =
	R"(#version 330 core
	   in vec3 fColor;
	   out vec4 FragColor;
	   void main() {
	       FragColor = vec4(fColor, 1.0f);
	   })";

Vec3 translate(0.0f);
Vec3 angles(0.0f);
Vec3 scale(1.0f);

Vec3 cameraPosition(0.0f, 0.0f, 2.0f);
Vec3 cameraRotation(0.0f, 0.0f, 0.0f);
bool isPerspectiveCamera = false;

int Window::init(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
	mData.width = aWindowWidth;
	mData.height = aWindowHeight;
	mData.title = std::string(aTitle);

	LOG_INFO("Creating window {0} ({1}, {2})", mData.title, mData.width, mData.height);

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

	mWindow = glfwCreateWindow(aWindowWidth, aWindowHeight, aTitle, nullptr, nullptr);
	if (!mWindow)
	{
		LOG_ERROR("GLFW window creation failed");
		glfwTerminate();
		return -2;
	}
	LOG_INFO("GLFW window created succesfully");

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
		Renderer::viewport(width, height);
	});

	GUIModule::onWindowCreate(mWindow);

	if (mShaderProgram.init(vertexShaderCode, fragmentShaderCode) == false)
		return -4;

	BufferLayout layout({ ShaderData::Type::FLOAT3, ShaderData::Type::FLOAT3 });

	mVBO.init(vertices, layout);
	mEBO.init(indices);

	mVAO.init();
	mVAO.addVertexBuffer(mVBO);
	mVAO.setIndexBuffer(mEBO);

	mCamera.init(cameraPosition, cameraRotation);

	return 0;
}

void Window::shutdown()
{
	mEBO.clear();
	mVBO.clear();
	mVAO.clear();

	mShaderProgram.clear();

	GUIModule::onWindowClose();

	glfwDestroyWindow(mWindow);
	glfwTerminate();

	LOG_INFO("Window terminated");
}

void Window::onUpdate()
{
	Renderer::clearColor(Vec4(mBackgroundColor.x, mBackgroundColor.y, mBackgroundColor.z, 1.0f));
	Renderer::clear();

	Mat4 transformMat;
	transformMat.transform(translate, angles, scale);

	mCamera.setTransform(cameraPosition, cameraRotation);
	mCamera.setProjectionMode(isPerspectiveCamera ? Camera::ProjectionMode::PERSPECTIVE : Camera::ProjectionMode::ORTHO);

	mShaderProgram.bind();

		mShaderProgram.setMat4("uModel", transformMat);
		mShaderProgram.setMat4("uViewProject", mCamera.getViewProjectionMatrix());

		Renderer::draw(mVAO);

	mShaderProgram.unbind();

	GUIModule::onDrawBegin();

	GUIModule::ShowExampleAppDockSpace();

	//ImGui::ShowDemoWindow();
	ImGui::Begin("Editor Window");
	ImGui::ColorEdit3("Background color", mBackgroundColor.toPtr());
	ImGui::SliderFloat3("Translate", translate.toPtr(), -5.0f, 5.0f);
	ImGui::SliderFloat3("Rotate", angles.toPtr(), -180.0f, 180.0f);
	ImGui::SliderFloat3("Scale", scale.toPtr(), 0.0f, 2.0f);
	ImGui::SliderFloat3("Camera Position", cameraPosition.toPtr(), -5.0f, 5.0f);
	ImGui::SliderFloat3("Camera Rotation", cameraRotation.toPtr(), -180.0f, 180.0f);
	ImGui::Checkbox("Perspective camera", &isPerspectiveCamera);
	ImGui::End();

	GUIModule::onDrawEnd();

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

} // namespace Delta
