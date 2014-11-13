#include "ResourceLoader.hpp"
#include <cassert>
#include <fstream>

ResourceLoader::ResourceLoader()
  : mDataPath("")
{
}

void ResourceLoader::SetDataPath(const std::string& path)
{
  mDataPath = path;
}

std::vector<char> ResourceLoader::LoadResource(const char* path)
{
  assert(path);
  std::string thePath = path;
  return LoadResource(thePath);
}

std::vector<char> ResourceLoader::LoadResource(const std::string& path)
{
  std::string filename = mDataPath + "/" + path;
  std::ifstream infile(filename, std::ios::binary);
  return std::vector<char>((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
}

std::string ResourceLoader::LoadFileAsString(const char* path)
{
  assert(path);    
  std::string thePath = path; 
  return LoadFileAsString(thePath);
}

std::string ResourceLoader::LoadFileAsString(const std::string& path)
{
  std::string filename = mDataPath + "/" + path;  
  std::ifstream infile(filename, std::ios::binary);
  return std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
}