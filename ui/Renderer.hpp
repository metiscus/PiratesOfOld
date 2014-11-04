#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>
#include <unordered_map>
#include <string>

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
  void clear(float r, float g, float b, float a);
    
  // texture functions
  GLuint loadTexture(std::string filename);
  GLuint getTexture(std::string filename);
  void freeTexture(GLuint texture);
  void bindTexture(GLuint texture);
  
  // shader functions
  GLuint loadShader(std::string filename, ShaderType type);
  bool compileShader(GLuint shader);
  GLuint getShader(std::string filanem);
  void freeShader(GLuint shader);
  
  GLuint createProgram(std::string name);
  void useProgram(GLuint program);
  bool linkProgram(GLuint program);
  bool addShader(GLuint shader);

  // Draw functions
  void drawPoint( const Vertex& point );
  void drawLine( const Vertex& from, const Vertex& to );
  void drawQuad( const Vertex& from, const Vertex& to );
  
private:
  SDL_Window* mWindow;
  SDL_GLContext mContext;
  
  std::unordered_map<std::string, GLuint> mTextures;
  std::unordered_map<std::string, GLuint> mPrograms;
  std::unordered_map<std::string, GLuint> mShaders;
  std::unordered_map<std::string, GLuint> mUniforms;
  
  GLuint  mCurrentProgram;
  bool    mIsBlendingEnabled;
  bool    mIsDepthTestEnabled;
  bool    mIsTexturingEnabled;
  GLfloat mClearColor[4];
};

#endif