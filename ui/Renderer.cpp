#include "Renderer.hpp"

#include <cstdio>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

#include "stb/stb_image.h"
#include "stb/stb_truetype.h"

Renderer::Renderer(int x, int y, int w, int h, std::string title)
  : mWindow(nullptr)
  , mCurrentProgram(0)
  , mCurrentTexture(0)
  , mIsBlendingEnabled(false)
  , mIsDepthTestEnabled(false)
  , mIsTexturingEnabled(false)
{
  mClearColor[0] = mClearColor[1] = mClearColor[2] = mClearColor[3] = 0.f;
  
  mWindow = SDL_CreateWindow( title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL );
  if(!mWindow)
  {
    printf("Failed to create a window.\n");
    exit(1);
  }
  
  mContext = SDL_GL_CreateContext(mWindow);
  SDL_GL_MakeCurrent(mWindow, mContext);
  if(!glewInit())
  {
    printf("Failed to initialize GLEW.\n");
  }
}

Renderer::~Renderer()
{
  
}
 
void Renderer::enableBlending()
{
  if(!mIsBlendingEnabled){
    glEnable(GL_BLEND);
    mIsBlendingEnabled = true;
  }
}

void Renderer::disableBlending()
{
  if(mIsBlendingEnabled){
    glDisable(GL_BLEND);
    mIsBlendingEnabled = false;
  }
}

void Renderer::enableDepthTest()
{
  if(!mIsDepthTestEnabled){
    glEnable(GL_DEPTH_TEST);
    mIsDepthTestEnabled = true;
  }
}

void Renderer::disableDepthTest()
{
  if(mIsDepthTestEnabled){
    glDisable(GL_DEPTH_TEST);
    mIsDepthTestEnabled = false;
  }
}

void Renderer::enableTexturing()
{
  if(!mIsTexturingEnabled){
    glEnable(GL_TEXTURE_2D);
    mIsTexturingEnabled = true;
  }
}

void Renderer::disableTexturing()
{
  if(mIsTexturingEnabled){
    glDisable(GL_TEXTURE_2D);
    mIsTexturingEnabled = false;
  }
}

void Renderer::clear(bool depth)
{
  if(depth) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
  else {
    glClear( GL_COLOR_BUFFER_BIT );
  }
}

void Renderer::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
  glClearColor(r, g, b, a);
}

GLuint Renderer::loadTexture(std::string filename)
{
  int x, y, c;
  uint8_t *ptr = stbi_load( filename.c_str(), &x, &y, &c, 4 );
  if(ptr){
    GLuint tex;
    glGenTextures(1, &tex);
    if(!mIsBlendingEnabled){
      enableTexturing();
    }
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, mCurrentTexture);
    mTextures[filename] = tex;
    stbi_image_free( ptr );
    
    return tex;
  }
  else {
    return 0;
  }
}

GLuint Renderer::getTexture(std::string filename)
{
  if(mTextures.count(filename)>0){
    return mTextures[filename];
  }
  return 0;
}

void Renderer::freeTexture(GLuint texture)
{
  auto begin = mTextures.begin();
  for( ; begin!=mTextures.end(); ++begin )
  {
    if(begin->second == texture)
    {
      mTextures.erase(begin);
      glDeleteTextures(1, &texture);
      break;
    }
  }
}

void Renderer::bindTexture(GLuint texture)
{
  if(mCurrentTexture != texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
    mCurrentTexture = texture;
  }
}

GLuint Renderer::loadShader(std::string filename, ShaderType type)
{
  std::string file, line;
  std::fstream infile(filename.c_str());
  while(infile.is_open() && !infile.eof())
  {
    std::getline(infile, line);
    file += (line + "\n");
  }
  
  GLuint shader;
  switch(type)
  {
    case Shader_Fragment: {
      shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    case Shader_Vertex: {
      shader = glCreateShader(GL_VERTEX_SHADER);
    }
  }
  
  setShaderSource(shader, file);
  
  mShaders[filename] = shader;
  return shader;
}

void Renderer::setShaderSource(GLuint shader, std::string source)
{
  // send the shader source to OpenGL
  char *shaderSource = strdup(source.c_str());
  if(shaderSource) {
    glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);
    free(shaderSource); 
  }
}

bool Renderer::compileShader(GLuint shader)
{
  GLint ret;
  
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
  if (!ret)
  {
    GLint log_length;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    log = (char *)malloc(log_length);
    if(log) {
      glGetShaderInfoLog(shader, log_length, NULL, log);
      printf("Shader failed to compile with error %s\n", log);
      free(log);
    }
    return false;
  }
  else {
    return true;
  }
}

GLuint Renderer::getShader(std::string filename)
{
  if(mShaders.count(filename)>0)
  {
    return mShaders[filename];
  }
  else {
    return 0;
  }
}

void Renderer::freeShader(GLuint shader)
{
  for(auto itr = mShaders.begin(); itr!=mShaders.end(); ++itr)
  {
    if(itr->second == shader)
    {
      glDeleteShader(shader);
      mShaders.erase(itr);
      break;
    }
  }
}

// program functions
GLuint Renderer::createProgram(std::string name)
{
  GLuint program = glCreateProgram();
  mPrograms[name] = program;
  return program;
}

void Renderer::useProgram(GLuint program)
{
  if(mCurrentProgram != program)
  {
    mCurrentProgram = program;
    glUseProgram(program);
  }
}

bool Renderer::linkProgram(GLuint program)
{
  glLinkProgram(program);
  GLint program_ok;
  glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
  if (!program_ok)
  {
    GLint log_length;
    char *log;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    log = (char *)malloc(log_length);
    if(log) {
      glGetProgramInfoLog(program, log_length, NULL, log);
      printf("program failed to link with error %s\n", log);
      free(log);

    }
    return false;
  }
  return true;
}

bool Renderer::addShader(GLuint program, GLuint shader)
{
  glAttachShader(program, shader);
  return true;
}

// font functions
GLuint Renderer::createFont(std::string filename)
{
  const uint32_t fontBufferSize = 1<<25;
  uint8_t fontBuffer[fontBufferSize];
  const uint32_t fontTextureSize = 512;
  const uint32_t fontPixelHeight = 16;
  uint8_t fontBitmap[fontTextureSize*fontTextureSize];
  stbtt_fontinfo font;
  
  FILE *fp = fopen(filename.c_str(), "rb");
  if(fp) {
    FontInfo fntInfo;
    fread(fontBuffer, 1, fontBufferSize, fp);
    stbtt_InitFont(&font, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer,0));
    stbtt_BakeFontBitmap(fontBuffer, 0, (float)fontPixelHeight, fontBitmap, fontTextureSize, fontTextureSize, 16, fntInfo.sCharCount, fntInfo.chars);
    
    // convert the bmp into a texture
    enableTexturing();
    glGenTextures(1, &fntInfo.texture);
    glBindTexture(GL_TEXTURE_2D, fntInfo.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fontTextureSize, fontTextureSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, fontBitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // restore old texture
    glBindTexture(GL_TEXTURE_2D, mCurrentTexture);

    // store
    mFonts[filename] = fntInfo;
    return fntInfo.texture;
  }
  
  return 0;
}

GLuint Renderer::getFont(std::string filename)
{
  if(mFonts.count(filename) > 0)
  {
    return mFonts[filename].texture;
  }
  else {
    return 0;
  }
}

void Renderer::freeFont(GLuint font)
{
  for(auto itr=mFonts.begin(); itr!=mFonts.end(); ++itr)
  {
    if(itr->second.texture == font)
    {
      glDeleteTextures(1, &itr->second.texture);
      mFonts.erase(itr);
      break;
    }
  }
}

// Draw functions
void drawPoint( const Vertex& point );
void drawLine( const Vertex& from, const Vertex& to );
void drawQuad( const Vertex& from, const Vertex& to );
void drawText( GLuint font, const Vertex& start, const std::string& text );