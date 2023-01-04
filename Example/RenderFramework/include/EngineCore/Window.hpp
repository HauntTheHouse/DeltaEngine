#pragma once

#include "EngineCore/Event.hpp"
#include "EngineCore/Rendering/OpenGL/GlShaderProgram.hpp"
#include "EngineCore/Rendering/OpenGL/GlVertexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/GlIndexBuffer.hpp"
#include "EngineCore/Rendering/OpenGL/GlVertexArray.hpp"

struct GLFWwindow;

class Window
{
public:
	using EventCallback = std::function<void(EventBase&)>;

	Window() = default;
	~Window() = default;

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(const Window&&) = delete;

	int init(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle);
	void shutdown();
	void onUpdate();

	unsigned int getWidth() const { return mData.width; }
	unsigned int getHeight() const { return mData.height; }

	void setEventCallback(EventCallback aEventCallbeck) { mData.eventCallback = std::move(aEventCallbeck); }

private:
	struct WindowParameters
	{
		unsigned int width;
		unsigned int height;
		std::string title;
		EventCallback eventCallback;
	};

	GLFWwindow* mWindow{ nullptr };
	WindowParameters mData;

	GlShaderProgram mShaderProgram;
	GlVertexBuffer mVBO;
	GlIndexBuffer mEBO;
	GlVertexArray mVAO;

	float mBackgroundColor[3] = { 0.2f, 0.2f, 0.2f };

	static bool sIsGLFWInitialized;
};
