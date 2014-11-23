#ifndef WORLDMAPMODEL_HPP_
#define WORLDMAPMODEL_HPP_

#include "engine/Model.hpp"
#include "gameplay/Map.hpp"
#include <memory>

class WorldMapView;
class Map;

class WorldMapModel : public Model
{
public:
  void SetMap(std::shared_ptr<Map> map);
  
private:
  std::shared_ptr<Map> mMap;
  float mCenterX;
  float mCenterY;
};

#endif