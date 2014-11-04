#version 330
uniform sampler2D Sampler;

in vec2 texCoordOut;

layout(location=0) out vec4 fragColor;

void main()
{
  fragColor = texture2D(Sampler, texCoordOut).rgba;
  //fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}