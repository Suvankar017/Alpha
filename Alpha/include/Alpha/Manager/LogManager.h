#pragma once

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

namespace Alpha
{
	class LogManager
	{
	public:
		LogManager() = default;
		~LogManager() = default;

		static void Init();
		static void Shutdown();
	};
}

#endif // !LOGMANAGER_H
