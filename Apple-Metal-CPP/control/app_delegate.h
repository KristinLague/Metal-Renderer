//
//  app_delegate.h
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//

#pragma once
#include "../config.h"
#include "view_delegate.h"

class AppDelegate : public NS::ApplicationDelegate
{
    public:
        ~AppDelegate();
    
    virtual void applicationWillFinishLaunching(NS::Notification* notification) override;
    virtual void applicationDidFinishLaunching(NS::Notification* notification) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) override;
    
private:
    NS::Window* window;
    MTK::View* mtkView;
    MTL::Device* device;
    ViewDelegate* viewDelegate = nullptr;
    
};
