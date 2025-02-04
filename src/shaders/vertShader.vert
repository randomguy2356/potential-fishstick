#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vCol;
layout (location = 2) in vec2 vtexCoord;

uniform vec2 offset;

out vec4 vertexColor;
out vec2 texCoord;

int scale = 1;
void main(){
    vec2 xyPos = vec2(vPos.xy);
    gl_Position = vec4((xyPos / scale) + (offset / 100), vPos.z, 1.0f);
    vertexColor = vec4(vCol, 1.0);
    texCoord = vtexCoord;
}
