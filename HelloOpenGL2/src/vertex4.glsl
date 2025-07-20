#version 330 core

layout (location = 0) in vec3 a_pos;

uniform float offset;

out vec3 color;

void main () {
	gl_Position = vec4(a_pos + vec3(offset, .0f, .0f), 1.f);
	color = a_pos + vec3(offset, .0f, .0f);
}