#version 330
uniform sampler2D Sampler;

in vec2 texCoordOut;
in vec4 colorOut;

layout(location=0) out vec4 fragColor;

void main()
{
  fragColor = colorOut + texture2D(Sampler, texCoordOut).rgba;
}