#version 430 core
layout(location = 0) in vec4 pos;
layout(location = 1) uniform vec4 mov;
layout(location = 2) uniform mat4 p;
layout(location = 3) uniform mat4 v;

layout(location = 4) uniform mat4 c;
void main(){gl_Position = p*v*pos;}
