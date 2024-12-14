//
//  view_delegate.h
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//

#pragma once
#include "config.h"
#include "../view/renderer.h"

class ViewDelegate : public MTK::ViewDelegate{
    
public:
    ViewDelegate(MTL::Device* device);
    virtual ~ViewDelegate() override;
    virtual void drawInMTKView(MTK::View* view) override;
    
private:
    Renderer* renderer;
};
