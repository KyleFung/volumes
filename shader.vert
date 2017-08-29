#version 150 core

in vec3 position;
in vec3 texcoord;

out vec3 texCoord;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * trans * vec4(position, 1.0);
    texCoord = texcoord;
}
