#ifndef GAMEWORLD_HPP_
#define GAMEWORLD_HPP_

#include "Date.hpp"
#include "Nation.hpp"
#include "Pirate.hpp"
#include "Territory.hpp"

#include <map>
#include <string>

class GameWorld
{
public:
  GameWorld(std::string dataPath);
  
  void setPirate(Pirate pirate);
  Pirate& getPirate();
  const Pirate& getPirate() const;
  
  void setDate(Date date);
  Date& getDate();
  const Date& getDate() const;
  
  void addTerritory(int id, Territory territory);
  Territory& getTerritory(int id);
  Territory getTerritory(int id) const;
  
  void addNation(Nation nation);
  Nation& getNation(Nation::NationId id);
  Nation getNation(Nation::NationId id) const;
  
private:
  Date mDate;
  Pirate mPirate;
  std::map<int, Territory> mTerritories;
  std::map<Nation::NationId, Nation> mNations;
  std::string mDataPath;
};

#endif