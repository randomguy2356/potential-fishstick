#version 330 core
precision highp float;
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vCol;

uniform float xoffset;
uniform float yoffset;

out vec4 vertexColor;

void main(){
    gl_Position = vec4(vPos.x + xoffset / 100, vPos.y + yoffset / 100, vPos.z, 1.0);
    vertexColor = vec4(vCol, 1.0);
}
