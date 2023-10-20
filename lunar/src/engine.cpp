#include "engine.h"
#include <iostream>
#include "sdl2/SDL.h"

namespace lunar {
     void GetInfo()
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

    bool Init() {
        bool val = true;

        if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
            std::cout << "Error initalizing SDL2" << SDL_GetError()<< std::endl;
            val = false;
        }else {
            SDL_version version;
            SDL_VERSION(&version);
            std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << std::endl;
        }

        return val;
    }

    void Shutdown(){
        SDL_Quit();
    }
}
