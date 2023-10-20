#include "engine.h"
#include <iostream>
#include "sdl2/SDL.h"

namespace lunar {
     void Engine::GetInfo()
    {
    #ifdef LUNAR_CONFIG_DEBUG
        std::cout << "Configuration: DEBUG" << std::endl;
    #endif
    #ifdef LUNAR_CONFIG_RELEASE
        std::cout << "Configuration: RELEASE" << std::endl;
    #endif
    #ifdef LUNAR_PLATFORM_WINDOWS
        std::cout << "Platform: WINDOWS" << std::endl;
    #endif
    #ifdef LUNAR_PLATFORM_LINUX
        std::cout << "Platform: LINUX" << std::endl;
    #endif
    #ifdef LUNAR_PLATFORM_MAC
        std::cout << "Platform: MAC" << std::endl;
    #endif
    }

    bool Engine::Init() {
        bool val = true;

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
            std::cout << "Error initalizing SDL2" << SDL_GetError()<< std::endl;
            val = false;
        }else {
            SDL_version version;
            SDL_VERSION(&version);
            std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << std::endl;

            if (_window.Create())
			{
				val = true;
				_isRunning = true;
			}
        }

        if (!val)
		{
			std::cout << "Engine initialization failed. Shutting down." << std::endl;
			Shutdown();
		}


        return val;
    }

    void Engine::Shutdown(){
        _isRunning = false;
		_window.Shutdown();
        SDL_Quit();
    }

    Engine& Engine::instance(){
        if(!_instance){
            _instance = new Engine();
        }

        return *_instance;
    }

    void Engine::Run()
	{
		if (Init())
		{
			// core loop
			while (_isRunning)
			{
				_window.PumpEvents();
			}

			Shutdown();
		}
	}

    Engine* Engine::_instance = nullptr;

    Engine::Engine(): _isRunning(false){
        GetInfo();
    }
}
