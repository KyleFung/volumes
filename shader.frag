#version 150 core

in vec3 texCoord;

out vec4 outColor;

uniform vec3 cameraPos;
uniform sampler3D sampler;

float max3 (vec3 v) {
    return max (max (v.x, v.y), v.z);
}

void main()
{
    vec3 direction = texCoord - cameraPos;
    direction = 0.001f * direction / length(direction);
    outColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec3 pos = texCoord;
    for(int i = 0; i < 1000; i++) {
        pos += direction;
        if(max3(pos) > 1.0f) {
            break;
        }
        outColor += 0.001f * pow(1.0f - texture(sampler, pos), vec4(3.0f));
    }
}
