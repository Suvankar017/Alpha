#include "pch.h"
#include "Alpha/Core/Engine.h"

int main()
{
	Alpha::Core::Engine* engine = Alpha::Core::Engine::Create();
	engine->Run();
	Alpha::Core::Engine::Destory(engine);

	system("pause");
	return 0;
}