#version 330 core

in vec2 texture_coord;
in vec3 color;

out vec4 fragment_color;

uniform sampler2D base_texture;
uniform sampler2D noise_texture;

void main () {
    fragment_color = mix(texture(base_texture, texture_coord), texture(noise_texture, texture_coord), 0.65f) * vec4(color, 1.f);
    // fragment_color = vec4(color, 1.f);
}