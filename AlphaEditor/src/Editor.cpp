#include "Alpha/Core/App.h"
#include "Alpha/Debug/Log.h"

#include "Alpha/Event/ApplicationEvent.h"
#include "Alpha/Manager/EventManager.h"

class Editor : public Alpha::App
{
public:
	Editor()
	{
		Alpha::EventManager eventManager;
		Alpha::WindowResizeEvent* e = new Alpha::WindowResizeEvent(10, 5);
		eventManager.Submit(e);
		eventManager.Flush();
	}

	~Editor()
	{

	}

	virtual void OnUpdate() override
	{
		
	}

private:

};

Alpha::App* Alpha::CreateApp()
{
	return new Editor();
}

void Alpha::DestroyApp(Alpha::App*& app)
{
	if (app == nullptr) return;
	delete app;
	app = nullptr;
}