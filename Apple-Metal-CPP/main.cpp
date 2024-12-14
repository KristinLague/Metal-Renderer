//
//  main.cpp
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//

//Needs to be written, at one point, only once in a program somewhere
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "config.h"
#include "control/app_delegate.h"

#include <iostream>

int main(int argc, const char * argv[]) {
    
    //Start a new autorelease pool for memory management
    NS::AutoreleasePool* autoreleasePool = NS::AutoreleasePool::alloc()->init();
    
    //Delegate added to the app as means to extend its behaviour
    AppDelegate controller;
    
    NS::Application* app = NS::Application::sharedApplication();
    app->setDelegate(&controller);
    app->run();
    
    autoreleasePool->release();
    
    return 0;
}
