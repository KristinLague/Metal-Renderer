//
//  renderer.cpp
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//

#include "renderer.h"

Renderer::Renderer(MTL::Device* device):
device(device->retain())
{
    commandQueue = device->newCommandQueue();
    buildPipeline();
}

Renderer::~Renderer() {
    commandQueue->release();
    device->release();
}

void Renderer::buildPipeline(){
    std::ifstream file;
    file.open("shaders/triangle.metal");
    std::stringstream reader;
    reader << file.rdbuf();
    std::string raw_string = reader.str();
    
    //Needs to be a ns string so that the device library creation function can read it - strange AF!
    NS::String* source_code = NS::String::string(raw_string.c_str(), NS::StringEncoding::UTF8StringEncoding);
    
    //Library that constructs functions from the source code
    NS::Error* error = nullptr;
    MTL::CompileOptions* options = nullptr;
    MTL::Library* library = device->newLibrary(source_code,options,&error);
    if(!library){
        std::cout << error->localizedDescription()->utf8String() << std::endl;
    }
    
    //Now we need to specify the names of our shader functions and tell the library to load them in
    NS::String* vertexName = NS::String::string("vertexMain", NS::StringEncoding::UTF8StringEncoding);
    MTL::Function* vertexMain = library->newFunction(vertexName);
    
    NS::String* fragmentName = NS::String::string("fragmentMain", NS::StringEncoding::UTF8StringEncoding);
    MTL::Function* fragmentMain = library->newFunction(fragmentName);
    
    //Make a pipeline which uses these functions
    MTL::RenderPipelineDescriptor* descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    descriptor->setVertexFunction(vertexMain);
    descriptor->setFragmentFunction(fragmentMain);
    
    //Set pixel settings - need to look into this more, I am confused
    descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm_sRGB);
    
    trianglePipeline = device->newRenderPipelineState(descriptor, &error);
    if(!trianglePipeline){
        std::cout << error->localizedDescription()->utf8String() << std::endl;
    }
    
    //Manually free them again
    descriptor->release();
    vertexMain->release();
    fragmentMain->release();
    library->release();
    

}

void Renderer::draw(MTK::View* view){
    
    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();
    
    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();
    MTL::RenderPassDescriptor* renderPass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(renderPass);
    
    //Here we need to load the pipeline which has the shaders (check build)
    encoder->setRenderPipelineState(trianglePipeline);

    
    //Call shader
    encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle,NS::UInteger(0), NS::UInteger(3));
    
    
    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();
    
    pool->release();
}
