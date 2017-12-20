#version 330 core

in vec3 ourColour;
out vec4 colour;

void main()
{
	colour = vec4(ourColour,1.0f);
}