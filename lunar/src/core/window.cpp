#include "core/window.h"
#include "engine.h"
#include "log.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "glad/glad.h"

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
		_window = SDL_CreateWindow("LunarGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!_window)
		{
			LUNAR_ERROR("Error creating window: {}", SDL_GetError());
			return false;
		}

		#ifdef HIPPO_PLATFORM_MAC
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		#endif


		//opengl SDL window setup
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_SetWindowMinimumSize(_window, 200, 200);

		//create opengl context 
		_GLContext = SDL_GL_CreateContext(_window);
		if (_GLContext == nullptr)
		{
			LUNAR_ERROR("Error creating OpenGL context: {}", SDL_GetError());
			return false;
		}

		gladLoadGLLoader(SDL_GL_GetProcAddress);

		// TODO: Move this to a renderer initialization
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(
			static_cast<float>(0x64) / static_cast<float>(0xFF),
			static_cast<float>(0x95) / static_cast<float>(0xFF),
			static_cast<float>(0xED) / static_cast<float>(0xFF),
			1
		);	//

		return true;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}

	void Window::BeginRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::EndRender()
	{
		SDL_GL_SwapWindow(_window);
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