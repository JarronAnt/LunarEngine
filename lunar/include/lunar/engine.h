#pragma once
#include "core/window.h"

namespace lunar {

    class Engine {
        public:
            static Engine& instance();
            ~Engine(){}

            void Run();
            inline void Quit() { _isRunning = false; }

            
            

        private:
            Engine();
            static Engine* _instance;

            void GetInfo();
            [[nodiscard]] bool Init();
            void Shutdown();
            bool _isRunning;
            core::Window _window;


    };  
}