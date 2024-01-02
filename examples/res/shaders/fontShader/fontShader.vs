#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexturePos;

out vec2 vTextureCoord;

uniform mat4 MVP;

void main(){
    vTextureCoord =  aTexturePos;
    gl_Position = MVP * vec4(aPos,1.0f);
}