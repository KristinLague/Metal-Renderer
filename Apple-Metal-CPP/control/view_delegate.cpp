//
//  view_delegate.cpp
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//

#include "view_delegate.h"

ViewDelegate::ViewDelegate(MTL::Device* device) : MTK::ViewDelegate(), renderer(new Renderer(device)){}

ViewDelegate::~ViewDelegate(){
    delete renderer;
}

void ViewDelegate::drawInMTKView(MTK::View* view){
    renderer->draw(view);
}
