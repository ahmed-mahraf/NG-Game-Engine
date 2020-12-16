#version 440 core

layout(location = 0) out vec4 colour;

in vec3 v_Position;
in vec4 v_Colour;

void main()
{
	colour = vec4 (v_Position * 0.5 + 0.5, 1.0);
	colour = v_Colour;
}