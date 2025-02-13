#version 330 core
out vec4 FragColor;

uniform vec3 color1;
uniform vec3 color2;

in float interpolation;

void main()
{
    FragColor = vec4(mix(color2, color1, interpolation), 1.0);
} 