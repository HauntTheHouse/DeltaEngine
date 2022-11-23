#include "Application.hpp"

Application::Application()
{
}

Application::~Application()
{
}

int Application::start(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle)
{
	// while (true)
	{
		onUpdate();
	}
	return 0;
}

void Application::onUpdate()
{
}
