#include <GL/glew.h>
#include <GL/gl.h>

#include "Renderer.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <string>

#include "stb/stb_image.h"
#include "stb/stb_truetype.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const std::string sProjectionMatrixUniformName = "ProjMat";
static const std::string sSamplerUniformName          = "Sampler";
static const std::string sFragmentLocationName        = "fragColor";

Renderer::Renderer(int x, int y, int w, int h, std::string title)
  : mWindow(nullptr)
  , mWidth(w)
  , mHeight(h)  
  , mCurrentProgram(0)
  , mCurrentTexture(0)
  , mIsBlendingEnabled(false)
  , mIsDepthTestEnabled(false)
  , mIsTexturingEnabled(false)
{
  fprintf(stderr, "renderer created %p\n", this);
  mClearColor[0] = mClearColor[1] = mClearColor[2] = mClearColor[3] = 0.f;
  
  mWindow = SDL_CreateWindow( title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL );
  if(!mWindow)
  {
    printf("Failed to create a window.\n");
    exit(1);
  }
  
  mContext = SDL_GL_CreateContext(mWindow);
  SDL_GL_MakeCurrent(mWindow, mContext);
  SDL_GL_MakeCurrent(mWindow, mContext);
  SDL_GL_SwapWindow(mWindow);

  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
  {
    printf("Failed to initialize GLEW.\n");
  }
  
  /*
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POINT_SPRITE);
  glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  */
}

Renderer::~Renderer()
{
  //\TODO: Write deinitialization code here
}
 
void Renderer::enableBlending()
{
  if(!mIsBlendingEnabled){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    stbi_image_free(ptr);
    
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
      break;
    }
    
    case Shader_Vertex: {
      shader = glCreateShader(GL_VERTEX_SHADER);
      break;
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
  ProgramInfo myProgram;
  myProgram.program = glCreateProgram();
  glGenSamplers(1, &(myProgram.sampler));
  glSamplerParameteri(myProgram.sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glSamplerParameteri(myProgram.sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //glSamplerParameteri(myProgram.sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  
  mPrograms[name] = myProgram;
  return myProgram.program;
}

void Renderer::useProgram(GLuint program)
{
  if(mCurrentProgram != program)
  {
    mCurrentProgram = program;
    glUseProgram(program);
    for(auto itr=mPrograms.begin(); itr!=mPrograms.end(); ++itr)
    {
      if(itr->second.program == program) {
	glActiveTexture(GL_TEXTURE0);
	glBindSampler(0, itr->second.sampler);
	glUniform1i(itr->second.samplerUniform, 0);

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 0, -1.0), glm::vec3(0, 0, 1.0), glm::vec3(0., -1., 0.f));
	viewMatrix = glm::inverse(viewMatrix);
	glm::mat4 projectionMatrix = glm::ortho((float)-mWidth/2.f, (float)mWidth/2.f, (float)-0.5*mHeight, (float)0.5*mHeight, (float)-10., (float)10.);
	
	projectionMatrix = projectionMatrix * viewMatrix;
	glUniformMatrix4fv(itr->second.projMatUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	break;
      }
    }
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
  
  // do a little bit of program setup
  glUseProgram(program);
  glBindFragDataLocation(program, 0, sFragmentLocationName.c_str());
  for(auto itr = mPrograms.begin(); itr!=mPrograms.end(); ++itr)
  {
    if(itr->second.program == program) {
      itr->second.projMatUniform = glGetUniformLocation(program, sProjectionMatrixUniformName.c_str());
      itr->second.samplerUniform = glGetUniformLocation(program, sSamplerUniformName.c_str());
      break;
    }
  }
  return true;
}

bool Renderer::addShader(GLuint program, GLuint shader)
{
  glAttachShader(program, shader);
  return true;
}

// font functions
GLuint Renderer::loadFont(std::string filename)
{
  const uint32_t fontBufferSize = 1<<25;
  uint8_t *fontBuffer = (uint8_t*)malloc(fontBufferSize);
  const uint32_t fontTextureSize = 512;
  const uint32_t fontPixelHeight = 32;
  const uint32_t firstChar = 32;
  uint8_t fontBitmap[fontTextureSize*fontTextureSize];
  stbtt_fontinfo font;
  
  FILE *fp = fopen(filename.c_str(), "rb");
  if(fp) {
    FontInfo fntInfo;
    fntInfo.textureSize = (float)fontTextureSize;
    fread(fontBuffer, 1, fontBufferSize, fp);
    stbtt_InitFont(&font, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer,0));
    stbtt_BakeFontBitmap(fontBuffer, 0, (float)fontPixelHeight, fontBitmap, fontTextureSize, fontTextureSize, firstChar, fntInfo.sCharCount, fntInfo.chars);
    
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
    mFontsReverse[fntInfo.texture] = filename;

    free(fontBuffer);
    return fntInfo.texture;
  }

  free(fontBuffer);
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
      mFontsReverse.erase(mFontsReverse.find(font));
      break;
    }
  }
}

// Draw functions
void Renderer::drawPoint(const Vertex& point)
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &(point.x));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, &(point.s));
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, &(point.r));
  glDrawArrays(GL_POINTS, 0, 1);
}

void Renderer::drawPoints( const std::vector<Vertex>& points )
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(points[0].x));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(points[0].s));
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(points[0].r));
  glDrawArrays(GL_POINTS, 0, points.size());
}

void Renderer::drawLine(const LineInfo& line)
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(line.from.x));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(line.from.s));
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(line.from.r));
  glDrawArrays(GL_LINES, 0, 2);
}

void Renderer::drawLines(const std::vector<LineInfo>& lines)
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(lines[0].from.x));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(lines[0].from.s));
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(lines[0].from.r));
  glDrawArrays(GL_LINES, 0, lines.size());
}

void Renderer::drawQuad(const QuadInfo& quad)
{
  std::vector<Vertex> drawData;
  drawData.push_back(quad.from);
  drawData.push_back(quad.to);
  drawData.push_back(Vertex(quad.from.x, quad.to.y, quad.from.z, quad.from.s, quad.to.t));
  
  drawData.push_back(quad.from);
  drawData.push_back(Vertex(quad.to.x, quad.from.y, quad.from.z, quad.to.s, quad.from.t));
  drawData.push_back(quad.to);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(drawData[0].x));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(drawData[0].s));
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(drawData[0].r));
  glDrawArrays(GL_TRIANGLES, 0, drawData.size());
}

void Renderer::drawQuads(const std::vector<QuadInfo>& quads)
{
  std::vector<Vertex> drawData;

  for(auto itr=quads.begin(); itr!=quads.end(); ++itr) {
    const QuadInfo &quad = *itr;
    Vertex baseVertex = quad.from;
    baseVertex.x = quad.from.x;
    baseVertex.y = quad.to.y;
    baseVertex.z = quad.from.z;
    baseVertex.s = quad.from.s;
    baseVertex.t = quad.to.t;
    drawData.push_back(quad.from);
    drawData.push_back(quad.to);
    drawData.push_back(baseVertex);
  
    baseVertex.x = quad.to.x;
    baseVertex.y = quad.from.y;
    baseVertex.z = quad.from.z;
    baseVertex.s = quad.to.s;
    baseVertex.t = quad.from.t;
    drawData.push_back(quad.from);
    drawData.push_back(baseVertex);
    drawData.push_back(quad.to);
  }
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(drawData[0].x));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(drawData[0].s));
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(drawData[0].r));
  glDrawArrays(GL_TRIANGLES, 0, drawData.size());
}

void Renderer::drawText(GLuint font, const Vertex& start, const std::string& text)
{
  assert(mFontsReverse.count(font)>0);
  assert(mFonts.count(mFontsReverse[font])>0);
  
  // find the font
  FontInfo& fntInfo = mFonts[mFontsReverse[font]];
  
  // generate a quad for each font
  Vertex cursor = start;
  cursor.y += 8;
  std::vector<QuadInfo> textQuads;
  
  for(int ii=0; ii<text.length(); ++ii)
  {
    QuadInfo letter;

    letter.from = cursor;
    letter.to = cursor;
    
    stbtt_aligned_quad quad;
    //fprintf(stderr, "%c %f $%f => ", text[ii], cursor.x, cursor.y);
    stbtt_GetBakedQuad(fntInfo.chars, 512, 512, ((int)text[ii]) - 32, &(cursor.x), &(cursor.y), &quad, 1);
    //fprintf(stderr, "%f $%f\n", cursor.x, cursor.y);
    letter.from.s = quad.s0;
    letter.from.t = quad.t0;
    letter.from.x = quad.x0;
    letter.from.y = quad.y0;
    letter.from.z = 0;
    
    letter.to.s = quad.s1;
    letter.to.t = quad.t1;
    letter.to.x = quad.x1;
    letter.to.y = quad.y1;
    letter.to.z = 0;
    textQuads.push_back(letter);
  }

  enableTexturing();
  glBindTexture(GL_TEXTURE_2D, fntInfo.texture);
  drawQuads(textQuads);
  glBindTexture(GL_TEXTURE_2D, mCurrentTexture);
}

void Renderer::begin()
{
  SDL_GL_MakeCurrent(mWindow, mContext);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
}

void Renderer::end()
{
  SDL_GL_SwapWindow(mWindow);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
}