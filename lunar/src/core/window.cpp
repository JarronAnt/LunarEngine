#include "core/window.h"
#include "engine.h"
#include "log.h"
#include "SDL2/SDL.h"
#include <iostream>

namespace lunar::core
{
	Window::Window() : _window(nullptr) {}
	Window::~Window()
	{
		if (_window)
		{
			Shutdown();
		}
	}

	bool Window::Create()
	{
		_window = SDL_CreateWindow("LunarGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		if (!_window)
		{
			LUNAR_ERROR("Error creating window: {}", SDL_GetError());
			return false;
		}

		return true;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}

	void Window::PumpEvents()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				Engine::instance().Quit();
				break;

			default:
				break;
			}
		}
	}
}