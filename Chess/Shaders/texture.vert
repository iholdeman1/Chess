#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 text;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	TexCoords = text;
  gl_Position = projection * model * vec4(position.x, position.y, 0.0, 1.0);
}
