#version 150 core

in vec3 texCoord;

out vec4 outColor;

uniform sampler3D sampler;

void main()
{
    outColor = texture(sampler, texCoord);
}
