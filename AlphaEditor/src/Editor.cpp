#include "Alpha/Core/App.h"
#include "Alpha/Debug/Log.h"

class Editor : public Alpha::Core::App
{
public:
	Editor()
	{

	}

	~Editor()
	{

	}

	virtual void OnUpdate() override
	{
		AP_INFO("Running {}", "Editor");
	}

private:

};

Alpha::Core::App* Alpha::Core::CreateApp()
{
	return new Editor();
}

void Alpha::Core::DestroyApp(Alpha::Core::App*& app)
{
	if (app == nullptr) return;
	delete app;
	app = nullptr;
}