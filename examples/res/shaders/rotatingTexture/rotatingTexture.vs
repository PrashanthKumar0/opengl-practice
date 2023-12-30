#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTextureCoord;


out vec2 vTextureCoord;

uniform mat4 MVP;

void main() {
    vTextureCoord = aTextureCoord;

    gl_Position = MVP * vec4(aPos,1.0);
}