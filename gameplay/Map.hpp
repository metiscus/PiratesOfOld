#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <vector>

class Map
{
public:
  enum TileId {
    Ocean,
    Shoal,
    Grass,
    Swamp,
    Woods,
    Mountain,
    Desert,
    Settlement
  };
  
  struct Tile {
    TileId id;
    int    info;
  };
  
  Map();
  
  void load(const std::string& filename);
  void save(const std::string& filename) const;
  
  void create(int width, int height, TileId baseTile);
  
  Tile& at(int x, int y);
  const Tile& at(int x, int y) const;
  
  int getWidth() const;
  int getHeight() const;
  
private:
  int mWidth;
  int mHeight;
  
  std::vector<Tile> mTiles;
};

#endif