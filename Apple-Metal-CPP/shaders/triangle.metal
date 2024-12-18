//
//  triangle.metal
//  Apple-Metal-CPP
//
//  Created by Kristin Lague on 14/12/2024.
//
#include <metal_stdlib>
using namespace metal;

constant float4 positions[] = {
    float4(-0.75,-0.75,0.0, 1.0),
    float4(0.75, -0.75, 0.0, 1.0),
    float4(0.0, 0.75, 0.0, 1.0)
};

constant half3 colors[] = {
    half3(1.0, 0.0, 0.0),
    half3(0.0, 1.0, 0.0),
    half3(0.0, 0.0, 1.0)
};

struct VertexPayload {
    float4 position [[position]]; //page 68 for meshvertex attributes
    half3 color; //makes it faster
};

//Checkout metal shader language specification document at page 99
//to learn more about the attributes for vertex function input arguments
//page 84 about function signifiers
VertexPayload vertex vertexMain(uint vertexID[[vertex_id]]){
    VertexPayload payload;
    
    payload.position = positions[vertexID];
    payload.color = colors[vertexID];
    
    return payload;
}


//stage_in to signify that this is an input variable
half4 fragment fragmentMain(VertexPayload frag [[stage_in]]){
    return half4(frag.color, 1.0);
}
