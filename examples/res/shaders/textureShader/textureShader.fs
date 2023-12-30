#version 330 core

in vec2 vTextureCoord;

out vec4 fragColor;

uniform sampler2D texture;

void main(){
    fragColor = texture2D(texture,vTextureCoord);
    // fragColor = texture2D(texture,vTextreCoord);
}