#ifndef TERRITORY_HPP_
#define TERRITORY_HPP_

#include "Nation.hpp"

#include <string>

class Territory
{
public:
  enum Type
  {
    TradingPost,
    SmallCity,
    LargeCity,
    SmallFort,
    LargeFort
  };
  
  Territory();
    
  int getId() const;
  void setId(int id);
  
  Type getType() const;
  void setType(Type type);

  void setName(std::string name);
  std::string getName() const;

  void setOwningPower(Nation::NationId owner);
  Nation::NationId getOwningPower() const;

  int getGarrison() const;
  void setGarrison(int garrison);

  bool getHasShipyard() const;
  bool getHasFort() const;
  bool getHasGovernor() const;
  
  void setHasShipyard(bool hasShip);
  void setHasFort(bool hasFort);
  void setHasGovernor(bool hasGov);

private:
  int mId;
  std::string mName;
  Nation::NationId mOwningPower;
  Type mType;
  int mGarrison;
  bool mHasGovernor;
  bool mHasFort;
  bool mHasShipyard;
};

#endif