#version 330 core

layout (location = 0) in vec3 pos_attrib;
layout (location = 1) in vec2 texture_coord_attrib;
layout (location = 2) in vec3 color_attrib;

out vec2 texture_coord;
out vec3 color;

void main () {
    gl_Position = vec4(pos_attrib, 1.f);

    texture_coord = texture_coord_attrib;
    color = color_attrib;
}