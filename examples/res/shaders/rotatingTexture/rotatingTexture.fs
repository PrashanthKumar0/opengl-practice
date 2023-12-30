#version 330 core

out vec4 fragColor;
in vec2  vTextureCoord;

uniform sampler2D texture;

void main() {
    fragColor = texture2D(texture, vTextureCoord);
}