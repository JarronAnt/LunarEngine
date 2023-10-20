#include<iostream>
#include "lunar/engine.h"

void main(void){

    lunar::Engine& engine = lunar::Engine::instance();
    engine.Run();
}