#pragma once

class Application
{
public:
	Application();
	virtual ~Application();

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(const Application&&) = delete;

	virtual int start(unsigned int aWindowWidth, unsigned int aWindowHeight, const char* aTitle);
	virtual void onUpdate();
};