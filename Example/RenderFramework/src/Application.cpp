#include "PCH.hpp"
#include "Application.hpp"

Application::Application()
{
}

Application::~Application()
{
}

int Application::start(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
	mWindow.init(aWindowWidth, aWindowHeight, aTitle);

	mEventDispatcher.addEventListener<WindowResizeEvent>([](WindowResizeEvent& event)
	{
		LOG_INFO("WindowResizeEvent: {0}x{1}", event.width, event.height);
	});
	mEventDispatcher.addEventListener<MouseMoveEvent>([](MouseMoveEvent& event)
	{
		LOG_INFO("MouseMovedEvent: x = {0}, y = {1}", event.x, event.y);
	});
	mEventDispatcher.addEventListener<WindowCloseEvent>([this](WindowCloseEvent& event)
	{
		LOG_INFO("MouseCloseEvent");
		mIsShouldClose = true;
	});

	mWindow.setEventCallback([this](EventBase& event)
	{
		mEventDispatcher.dispatch(event);
	});

	while (!mIsShouldClose)
	{
		mWindow.onUpdate();
		onUpdate();
	}

	mWindow.shutdown();
	return 0;
}
