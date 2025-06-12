#version 330 core
layout(location=0) in vec3 aPos;
out vec4 rColor;

uniform vec2 offset;

void main(){
    gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z, 1.0);
    rColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}