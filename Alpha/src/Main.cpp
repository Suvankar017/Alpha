#include "pch.h"
#include "Alpha/Core/Engine.h"

int main()
{
	Alpha::Engine* engine = Alpha::Engine::Create();
	engine->Run();
	Alpha::Engine::Destory(engine);

	system("pause");
	return 0;
}