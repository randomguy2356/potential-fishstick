#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vCol;

out vec4 vertexColor;

void main(){
    gl_Position = vec4(vPos * -1, 1.0);
    vertexColor = vec4(vCol, 1.0);
}
