#include <cassert>
#include "GameWorld.hpp"

GameWorld::GameWorld(std::string dataPath)
  : mDataPath(dataPath)
{
  
}

void GameWorld::setPirate(Pirate pirate)
{
  mPirate = pirate;
}

Pirate& GameWorld::getPirate()
{
  return mPirate;
}

const Pirate& GameWorld::getPirate() const
{
  return mPirate;
}

void GameWorld::setDate(Date date)
{
  mDate = date;
}

Date& GameWorld::getDate()
{
  return mDate;
}

const Date& GameWorld::getDate() const
{
  return mDate;
}

void GameWorld::addTerritory(int id, Territory territory)
{
  mTerritories[id] = territory;
}

Territory& GameWorld::getTerritory(int id)
{
  assert(mTerritories.count(id)>0);
  return mTerritories[id];
}

Territory GameWorld::getTerritory(int id) const
{
  std::map<int, Territory>::const_iterator itr;
  itr = mTerritories.find(id);
  if(itr != mTerritories.end())
  {
    return itr->second;
  }
  else {
    assert(false);
    return Territory();
  }
}

void GameWorld::addNation(Nation nation)
{
  mNations.insert(std::make_pair(nation.getId(), nation));
}

Nation& GameWorld::getNation(Nation::NationId id)
{
  return mNations[id];
}

Nation GameWorld::getNation(Nation::NationId id) const
{
  std::map<Nation::NationId, Nation>::const_iterator itr = mNations.find(id);
  if(itr != mNations.end())
  {
    return itr->second;
  }
  else {
    assert(false);
    return Nation(Nation::Invalid);
  }
}