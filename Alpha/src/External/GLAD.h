#pragma once

#ifndef GLAD_H
#define GLAD_H

namespace Alpha
{
	class GLAD
	{
	public:
		static void Init();

	private:
		static bool s_IsInitialized;
	};
}

#endif // !GLAD_H