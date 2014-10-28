#ifndef SHIP_HPP_
#define SHIP_HPP_

#include "Cargo.hpp"

enum ShipHull
{
  ShipHull_Sloop,
  ShipHull_Barque,
  ShipHull_WarGalleon,
  ShipHull_Galleon,
};

enum ShipType
{
  ShipType_Smuggler,
  ShipType_Merchant,
  ShipType_Military,
  ShipType_Treasure,
};

class Ship
{
public:
  Ship();
  
  static Ship generateTypicalShip( ShipType type );
  
  void setHull(ShipHull hull);
  ShipHull getHull() const;
  
  void setType(ShipType type);
  ShipType getType() const;
  
  int getMaxCannon() const;
  int getMaxSpeed() const;
  int getMaxTurn() const;
  int getMaxCargo() const;
  int getMaxCrew() const;
  
private:
  ShipHull mHull;
  ShipType mType;
  int mMaxCannon;
  int mMaxSpeed;
  int mMaxTurn;
  int mMaxCargo;
  int mMaxCrew;
  
  int mCargo[Cargo_Count];
};

#endif // SHIP_HPP_