#pragma once

namespace lunar::managers
{
	class LogManager
	{
	public:
		LogManager() = default;
		~LogManager() = default;

		void Initialize();
		void Shutdown();
	};
}