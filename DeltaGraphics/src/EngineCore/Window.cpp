#include "EngineCore/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

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

const GLchar* vertexShaderCode =
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

const GLchar* fragmentShaderCode =
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
	if (!glfwInit())
	{
		LOG_ERROR("Can't initialize GLFW!");
		return -1;
	}
	LOG_INFO("GLFW initialized succesfully");

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

	mCamera.init(cameraPosition, cameraRotation);

	return 0;
}

void Window::shutdown()
{
	mEBO.clear();
	mVBO.clear();
	mVAO.clear();

	mShaderProgram.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(mWindow);
	glfwTerminate();

	LOG_INFO("Window terminated");
}

void Window::onUpdate()
{
	glClearColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mShaderProgram.bind();

	Mat4 transformMat;
	transformMat.transform(translate, angles, scale);

	mCamera.setTransform(cameraPosition, cameraRotation);
	mCamera.setProjectionMode(isPerspectiveCamera ? Camera::ProjectionMode::PERSPECTIVE : Camera::ProjectionMode::ORTHO);

	mShaderProgram.setMat4("uModel", transformMat);
	mShaderProgram.setMat4("uViewProject", mCamera.getViewProjectionMatrix());

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
	ImGui::ColorEdit3("Background color", mBackgroundColor.toPtr());
	ImGui::SliderFloat3("Translate", translate.toPtr(), -5.0f, 5.0f);
	ImGui::SliderFloat3("Rotate", angles.toPtr(), -180.0f, 180.0f);
	ImGui::SliderFloat3("Scale", scale.toPtr(), 0.0f, 2.0f);
	ImGui::SliderFloat3("Camera Position", cameraPosition.toPtr(), -5.0f, 5.0f);
	ImGui::SliderFloat3("Camera Rotation", cameraRotation.toPtr(), -180.0f, 180.0f);
	ImGui::Checkbox("Perspective camera", &isPerspectiveCamera);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

} // namespace Delta
