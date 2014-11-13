#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include <map>
#include <string>
#include <vector>

class ResourceLoader
{
public:
  ResourceLoader();
   
  void SetDataPath(const std::string& path);
  
  std::vector<char> LoadResource(const char* path);
  std::vector<char> LoadResource(const std::string& path);
  std::string LoadFileAsString(const char* path);
  std::string LoadFileAsString(const std::string& path);
  
  
private:
  std::string mDataPath;
};

#endif