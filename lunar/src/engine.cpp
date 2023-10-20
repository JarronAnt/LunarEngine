#include "engine.h"
#include <iostream>
#include "sdl2/SDL.h"
#include "log.h"

namespace lunar {
     void Engine::GetInfo()
    {
		LUNAR_TRACE("LunarEngine v{}.{}", 0, 1);
#ifdef LUNAR_CONFIG_DEBUG
		LUNAR_DEBUG("Configuration: DEBUG");
#endif
#ifdef LUNAR_CONFIG_RELEASE
		LUNAR_DEBUG("Configuration: RELEASE");
#endif
#ifdef LUNAR_PLATFORM_WINDOWS
		LUNAR_WARN("Platform: WINDOWS");
#endif
#ifdef LUNAR_PLATFORM_LINUX
		LUNAR_WARN("Platform: LINUX");
#endif
#ifdef LUNAR_PLATFORM_MAC
		LUNAR_WARN("Platform: MAC");
#endif
    }

    bool Engine::Init() {
		bool val = false;
		LUNAR_ASSERT(!_isInitialized, "Attempting to call Engine::Initialize() more than once!"); //note this isnt an error idk why its showing as if it is 
		if(_isInitialized == false){
        	
		
			std::cout <<"PASS" << std::endl;
			_LogManager.Initialize();
			GetInfo();

			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				LUNAR_ERROR("Error initializing SDL2: {}", SDL_GetError());
			}
			else
			{
				SDL_version version;
				SDL_VERSION(&version);
				LUNAR_INFO("SDL {}.{}.{}", (int32_t)version.major, (int32_t)version.minor, (int32_t)version.patch);

				if (_window.Create())
				{
					val = true;
					_isRunning = true;
					_isInitialized = true;
				}
			}

			if (!val)
			{
				LUNAR_ERROR("Engine initialization failed. Shutting down.");
				Shutdown();
			}
		}
		return val;
    }

    void Engine::Shutdown(){
        _isRunning = false;
        _isInitialized = false;
        _LogManager.Shutdown();
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
