#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Colour;

out vec3 v_Position;
out vec4 v_Colour;

void main()
{
	v_Position = a_Position;
	v_Colour = a_Colour;
	gl_Position = vec4(a_Position, 1.0);
}