#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "stb/stb_truetype.h"

#include "ScriptEnvironment.hpp"
#include "Window.hpp"

#pragma pack(push, 1)
struct Vertex
{
  Vertex()
  : s(0.f), t(0.f), x(0.f), y(0.f), z(0.f), r(0.f), g(0.f), b(0.f), a(0.f) { }
  
  Vertex(GLfloat _x, GLfloat _y, GLfloat _z)
    : x(_x), y(_y), z(_z), r(0.f), g(0.f), b(0.f), a(0.f) { }
  
  Vertex(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _s, GLfloat _t)
    : s(_s), t(_t), x(_x), y(_y), z(_z), r(0.f), g(0.f), b(0.f), a(0.f) { }
    
  GLfloat s;
  GLfloat t;
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat r;
  GLfloat g;
  GLfloat b;
  GLfloat a;
};

struct LineInfo 
{
  Vertex from;
  Vertex to;
};

struct QuadInfo
{
  Vertex from;
  Vertex to;    
};
#pragma pack(pop)

class Renderer : public Scriptable
{
public:
  enum ShaderType {
    Shader_Vertex,
    Shader_Fragment
  };
  
  Renderer(std::shared_ptr<Window> window);
  virtual ~Renderer();
    
  static void RegisterMethods(ScriptEnvironment& env);
  //virtual void UnregisterMethods(ScriptEnvironment& env);
  
  void enableBlending();
  void disableBlending();
  void enableDepthTest();
  void disableDepthTest();
  void enableTexturing();
  void disableTexturing();
  void clear(bool depth);
  void clearColor(float r, float g, float b, float a);
    
  // texture functions
  GLuint loadTexture(std::string filename);
  GLuint getTexture(std::string filename);
  void freeTexture(GLuint texture);
  void bindTexture(GLuint texture);
  
  // shader functions
  GLuint loadShader(std::string filename, ShaderType type);
  void setShaderSource(GLuint shader, std::string source);
  bool compileShader(GLuint shader);
  GLuint getShader(std::string filename);
  void freeShader(GLuint shader);
  
  // program functions
  GLuint createProgram(std::string name);
  void useProgram(GLuint program);
  bool linkProgram(GLuint program);
  bool addShader(GLuint program, GLuint shader);

  // font functions
  GLuint loadFont(std::string filename);
  GLuint getFont(std::string filename);
  void freeFont(GLuint font);
  
  // Draw functions  
  void drawPoint(const Vertex& point);
  void drawPoints(const std::vector<Vertex>& points);
  void drawLine(const LineInfo& line);
  void drawLines(const std::vector<LineInfo>& lines);
  void drawQuad(const QuadInfo& quad);
  void drawQuads(const std::vector<QuadInfo>& quads);
  void drawText(GLuint font, const Vertex& start, const std::string& text);
  
  void begin();
  void end();
  
private: 
  std::shared_ptr<Window> mWindow;
  
  struct FontInfo {
    static const int sCharCount = 96;
    GLuint texture;
    float textureSize;
    stbtt_bakedchar chars [sCharCount];
  };
  
  struct ProgramInfo {
    GLuint projMatUniform;
    GLuint samplerUniform;
    GLuint program;
    GLuint sampler;
  };
  
  std::unordered_map<std::string, GLuint> mTextures;
  std::unordered_map<std::string, ProgramInfo> mPrograms;
  std::unordered_map<std::string, GLuint> mShaders;
  std::unordered_map<std::string, GLuint> mUniforms;
  std::unordered_map<std::string, FontInfo> mFonts;
  std::map<int, std::string> mFontsReverse;
  
  GLuint  mCurrentProgram;
  GLuint  mCurrentTexture;
  bool    mIsBlendingEnabled;
  bool    mIsDepthTestEnabled;
  bool    mIsTexturingEnabled;
  GLfloat mClearColor[4];
};

#endif