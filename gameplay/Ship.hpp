#ifndef SHIP_HPP_
#define SHIP_HPP_

#include <string>

class Ship
{
public:
  struct HullInfo
  {
    int id;
    std::string typeName;
    int maxCannon;
    int maxSpeed;
    int maxTurn;
    int maxCargo;
    int maxCrew;    
  };
  
  enum Role
  {
    Smuggler,
    Trader,
    Pirate,
    PirateHunter,
    TreasureBoat,
    WarBoat
  };
  
  Ship();
     
  const HullInfo& getHullInfo() const;
  void setHull(HullInfo info);
  
  Role getRole() const;
  void setRole(Role role);
  
private:
  HullInfo mHull;
  Role mRole;
};

#endif // SHIP_HPP_