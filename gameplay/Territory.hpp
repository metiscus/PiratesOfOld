#ifndef TERRITORY_HPP_
#define TERRITORY_HPP_

#include "Nations.hpp"

#include <string>

enum TerritoryType
{
    TerritoryType_TradingPost,
    TerritoryType_SmallCity,
    TerritoryType_LargeCity,
    TerritoryType_SmallFort,
    TerritoryType_LargeFort
};

class Territory
{
public:
    Territory();
    
    int getId() const;
    void setId(int id);
    
    TerritoryType getType() const;
    void setType(TerritoryType type);

    void setName(std::string name);
    std::string getName() const;

    void setLocationX(int x);
    void setLocationY(int y);
    int getLocationX() const;
    int getLocationY() const;

    void setOwningPower(Country owner);
    Country getOwningPower() const;

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
    int mLocationX;
    int mLocationY;
    Country mOwningPower;
    TerritoryType mType;
    int mGarrison;
    bool mHasGovernor;
    bool mHasFort;
    bool mHasShipyard;
};

#endif