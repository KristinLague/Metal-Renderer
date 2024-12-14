//
//  renderer.h
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//

#pragma once
#include "../config.h"

class Renderer{
public:
    Renderer(MTL::Device* device);
    ~Renderer();
    void draw(MTK::View* view);
    
private:
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
};
