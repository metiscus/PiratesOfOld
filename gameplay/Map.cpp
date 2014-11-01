#include <cassert>
#include <cstdio>
#include "Map.hpp"

Map::Map()
  : mWidth(0)
  , mHeight(0)
{
  ;
}

void Map::load(const std::string& filename)
{
  FILE *fp = std::fopen(filename.c_str(), "rb");
  if(fp)
  {
    std::fscanf(fp, "%d", &mWidth);
    std::fscanf(fp, "%d", &mHeight);

    // make sure the read was reasonable
    assert(mWidth>0); 
    assert(mWidth<10000);
    assert(mHeight>0); 
    assert(mHeight<10000);
    
    mTiles.resize(mWidth*mHeight);
    
    for(int ii=0; ii<mWidth*mHeight; ++ii)
    {
      int tileId;
      std::fscanf(fp, "%d", &tileId);
      mTiles[ii].id = static_cast<TileId>(tileId);
      std::fscanf(fp, "%d", &(mTiles[ii].info));
      
      if(std::feof(fp))
      {
	std::printf("Possibly corrupt map file %s.\n", filename.c_str());
	break;
      }
    }
    
    std::fclose(fp);
  }
  else {
    std::printf("Unable to open %s.\n", filename.c_str());
  }
}

void Map::save(const std::string& filename) const
{
  FILE *fp = std::fopen(filename.c_str(), "wb");
  if(fp)
  {
    std::fprintf(fp, "%d", mWidth);
    std::fprintf(fp, "%d", mHeight);
    for(int ii=0; ii<mWidth*mHeight; ++ii)
    {
      std::fprintf(fp, "%d", mTiles[ii].id);
      std::fprintf(fp, "%d", mTiles[ii].info);
    }
    
    std::fclose(fp);    
  }
  else {
    std::printf("Unable to open %s.\n", filename.c_str());
  }  
}

void Map::create(int width, int height, TileId baseTile)
{
  assert(width>0);
  assert(height>0);
  
  mWidth = width;
  mHeight = height;
  
  mTiles.clear();
  mTiles.resize(mWidth*mHeight);
  for(int ii=0; ii<mWidth*mHeight; ++ii)
  {
    mTiles[ii].id = baseTile;
  }
}

Map::Tile& Map::at(int x, int y)
{
  assert(x>=0 && x<mWidth);
  assert(y>=0 && y<mHeight);
  
  return mTiles[y*mWidth+x];
}

const Map::Tile& Map::at(int x, int y) const
{
  assert(x>=0 && x<mWidth);
  assert(y>=0 && y<mHeight);
  
  return mTiles[y*mWidth+x];  
}

int Map::getWidth() const
{
  return mWidth;
}

int Map::getHeight() const
{
  return mHeight;
}