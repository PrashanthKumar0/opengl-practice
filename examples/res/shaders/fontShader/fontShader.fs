#version 330 core

in vec2 vTextureCoord;

out vec4 fragColor;

uniform sampler2D bitmap;

void main(){
    float bitmap_intensity = texture2D(bitmap,vTextureCoord).r;
    // bitmap_intensity = ;
    fragColor = vec4(vec3(bitmap_intensity) , bitmap_intensity);
}