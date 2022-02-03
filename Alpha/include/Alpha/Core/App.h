#pragma once

#ifndef APP_H
#define APP_H

namespace Alpha
{
	class App
	{
	public:
		App();
		~App();

		virtual void OnUpdate();

	private:

	};

	App* CreateApp();
	void DestroyApp(App*& app);
}

#endif // !APP_H
