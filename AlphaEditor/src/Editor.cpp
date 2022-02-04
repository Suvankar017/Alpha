#include "Alpha/Core/App.h"
#include "Alpha/Debug/Log.h"

#include "Alpha/Core/Engine.h"
#include "Alpha/Input/Input.h"

class Editor : public Alpha::App
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
		if (Alpha::Input::GetKeyDown(Alpha::KeyCode::Escape))
			Alpha::Engine::Get().Stop();
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