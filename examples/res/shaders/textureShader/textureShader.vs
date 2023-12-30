#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexturePos;

out vec2 vTextureCoord;


void main(){
    vTextureCoord =  aTexturePos;
    gl_Position = vec4(aPos,1.0f);
}