#version 330
layout(location=0) in vec3 vertexIn;
layout(location=2) in vec2 texCoordIn;
layout(location=3) in vec4 colorIn;

out vec2 texCoordOut;
out vec4 colorOut;
uniform mat4 ProjMat;

void main()
{
  gl_Position = ProjMat * vec4(vertexIn.xyz, 1.f);
  texCoordOut = texCoordIn;
  colorOut    = colorIn;
}