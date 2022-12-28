#include "Application.hpp"
#include <iostream>

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
		std::cout << "WindowResizeEvent: width = " << event.width << ", height = " << event.height << "\n";
	});
	mEventDispatcher.addEventListener<MouseMoveEvent>([](MouseMoveEvent& event)
	{
		std::cout << "MouseMovedEvent : x = " << event.x << ", y = " << event.y << "\n";
	});
	mEventDispatcher.addEventListener<WindowCloseEvent>([this](WindowCloseEvent& event)
	{
		std::cout << "MouseCloseEvent\n";
		mIsShouldClose = true;
	});

	mWindow.setEventCallback([this](EventBase& event)
	{
		mEventDispatcher.dispatch(event);
		//std::cout << "EventCallback: width = " << event.width << ", height = " << event.height << "\n";
	});

	while (!mIsShouldClose)
	{
		mWindow.onUpdate();
		onUpdate();
	}

	mWindow.shutdown();
	return 0;
}
