#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>
#include <unordered_map>
#include <string>
#include "stb/stb_truetype.h"

struct Vertex
{
  GLfloat x;
  GLfloat y;
  GLfloat z;
  GLfloat s;
  GLfloat t;
};

class Renderer
{
public:
  enum ShaderType {
    Shader_Vertex,
    Shader_Fragment
  };
  
  Renderer(int x, int y, int w, int h, std::string title);
  ~Renderer();
  
  void enableBlending();
  void disableBlending();
  void enableDepthTest();
  void disableDepthTest();
  void enableTexturing();
  void disableTexturing();
  void clear(bool depth);
  void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    
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
  GLuint createFont(std::string filename);
  GLuint getFont(std::string filename);
  void freeFont(GLuint font);
  
  // Draw functions
  void drawPoint( const Vertex& point );
  void drawLine( const Vertex& from, const Vertex& to );
  void drawQuad( const Vertex& from, const Vertex& to );
  void drawText( GLuint font, const Vertex& start, const std::string& text );
  
private:
  SDL_Window* mWindow;
  SDL_GLContext mContext;
  
  struct FontInfo {
    static const int sCharCount = 96;
    GLuint texture;
    stbtt_bakedchar chars[sCharCount];
  };
  
  std::unordered_map<std::string, GLuint> mTextures;
  std::unordered_map<std::string, GLuint> mPrograms;
  std::unordered_map<std::string, GLuint> mShaders;
  std::unordered_map<std::string, GLuint> mUniforms;
  std::unordered_map<std::string, FontInfo> mFonts;
  
  GLuint  mCurrentProgram;
  GLuint  mCurrentTexture;
  bool    mIsBlendingEnabled;
  bool    mIsDepthTestEnabled;
  bool    mIsTexturingEnabled;
  GLfloat mClearColor[4];
};

#endif