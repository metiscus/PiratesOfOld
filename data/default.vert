#version 330
layout(location=0) in vec3 vertexIn;
layout(location=2) in vec2 texCoordIn;

out vec2 texCoordOut;
uniform mat4 ProjMat;

void main()
{
  gl_Position = ProjMat * vec4(vertexIn.xyz, 1.f);
  texCoordOut = texCoordIn;
}